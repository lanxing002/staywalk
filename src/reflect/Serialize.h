#pragma once

#ifndef _IN_REFLECT
//#include "Common.gen.h"
#include "reflect.h"

#include "rapidjson/document.h"
#include "fmt/format.h"

namespace json = rapidjson;
namespace staywalk {

	class World;

	class Comparer {
	public:
		template<typename T>
		static bool equal(const T& lhs, const T& rhs);

		template<typename T>
		static bool equal(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs);

		template<typename T> // vector
		static bool equal(const vector<T>& lhs, const vector<T>& rhs);

		template<typename TK, typename TV> // map
		static bool equal(const map<TK, TV>& lhs, const map<TK, TV>& rhs);
	};

	namespace reflect {
		class Dumper {
		public:
			enum class Status {
				Wait,
				Dumping,
				Done
			};

			Dumper(fs::path file_name);
			Dumper(const Dumper&) = delete;
			Dumper(Dumper&&) = delete;
			Dumper& operator=(const Dumper&) = delete;
			Dumper& operator=(Dumper&&) = delete;

			/**
			*@brief create a ofstream, and write type info
			*/
			void dump_world(const World& world);

			// wirte data to stream for all type which can serialize
			template<typename T>
			void write(const T& data, json::Value& value) { this->write_single(data, value); }

			template<typename T>
			void write(const std::vector<T>& data, json::Value& value) { this->write_vector<T>(data, value); }

			template<typename TK, typename TV>
			void write(const std::map<TK, TV>& data, json::Value& value) { this->write_map<TK, TV>(data, value); }

			template<typename T>
			void write(const std::shared_ptr<T>& obj, json::Value& value) {
				static_assert((std::is_base_of_v<staywalk::Object, T> || std::is_same_v<staywalk::Object, T>)
					&& "unsupport shared_ptr dump of other type");
				idtype dump_id = obj == nullptr ? kInvalidId : obj->get_guid();
				write(dump_id, value);
				if (dump_id != kInvalidId) this->dump_obj_impl(obj);
			}

			template<typename T, size_t N>
			void write_array(const T& data, json::Value& value); 

			template<>
			void Dumper::write(const SWCodeRef& obj, json::Value& value) {
				value.SetObject();
				obj->dump(value, *this);
			}

			json::Document& get_doc() { return doc_; }

		private:
			bool clear();

			/**
			*@brief create a ofstream, and write type info
			*/
			void dump_obj_impl(const shared_ptr<Object> obj);

			/**
			*@brief write common type dataread_single
			*/
			template<typename T>
			void write_single(const T&, json::Value& value);
			template<typename T>
			void write_vector(const vector<T>& data, json::Value& value);
			template<typename TKey, typename TVal>
			void write_map(const map<TKey, TVal>& data, json::Value& value);


			void write_single(const string& str, rapidjson::Value& value) {
				value = json::StringRef(str.c_str());
			}
			void write_single(const fs::path& path, rapidjson::Value& value) {
				value = json::StringRef(path.u8string().c_str());
			}
			void write_single(const bool& data, rapidjson::Value& value) { value.SetBool(data); }

			void write_single(const int& data, rapidjson::Value& value) { value.SetInt(data); }

			void write_single(const int64_t& data, rapidjson::Value& value) { value.SetInt64(data); }

			void write_single(const uint& data, rapidjson::Value& value) { value.SetUint(data); }

			void write_single(const uint64_t& data, rapidjson::Value& value) { value.SetUint64(data); }

			void write_single(const float& data, rapidjson::Value& value) { value.SetFloat(data); }
			
			void write_single(const double& data, rapidjson::Value& value) { value.SetDouble(data); }

			void write_single(const vec2& data, rapidjson::Value& value) {
				this->write_array<vec2, 2>(data, value);
			}
			void write_single(const vec3& data, rapidjson::Value& value) {
				write_array<vec3, 3>(data, value);
			}
			void write_single(const vec4& data, rapidjson::Value& value) {
				write_array<vec4, 4>(data, value);
			}
			void write_single(const quat& data, rapidjson::Value& value) {
				write_array<quat, 4>(data, value);
			}
			void write_single(const mat4& data, rapidjson::Value& value) {
				write_array<mat4, 4>(data, value);
			}

		private:
			hashtable<idtype, Status> status_table_;
			fs::path target_file_;
			json::Document doc_;
			json::Value real_objs_;
		};

		class Loader {
		public:
			enum class Status {
				Wait,
				Loading,
				Done
			};

			Loader(fs::path file_name);
			Loader(const Loader&) = delete;
			Loader(Loader&&) = delete;
			Loader& operator=(const Loader&) = delete;
			Loader& operator=(Loader&&) = delete;

			/**
			*@brief create a ifstream, and read type info
			*/
			void load(World& world);

			template<typename T>
			void read(T& data, json::Value& ivalue) { read_single(data, ivalue); }

			template<typename T>
			void read(std::vector<T>& data, json::Value& ivalue) { this->read_vector<T>(data, ivalue); }

			template<typename TK, typename TV>
			void read(std::map<TK, TV>& data, json::Value& ivalue) { this->read_map<TK, TV>(data, ivalue); }

			template<typename T>
			void read(std::shared_ptr<T>& data, json::Value& ivalue) {
				static_assert((std::is_same_v<::staywalk::Object, T> || std::is_base_of_v<staywalk::Object, T>)
					&& "unsupport shared_ptr load of other type");
				idtype id; read(id, ivalue);
				data = (id == kInvalidId) ? nullptr : pcast<T>(load_obj_impl(std::to_string(id)));
			}

			template<>
			void read(SWCodeRef& obj, json::Value& value) { obj->load(value, *this); }

			template<typename T, size_t N>
			void read_array(T& data, json::Value& ivalue);

			void clear();

		private:
			template<typename T>
			void read_single(T& data, json::Value& ivalue);

			void read_single(string& str, rapidjson::Value& value) {
				if (value.IsString()) str = std::string(value.GetString());
			}
			void read_single(fs::path& path, rapidjson::Value& value) {
				if (value.IsString()) path = std::string(value.GetString());
			}
			void read_single(bool& data, rapidjson::Value& value) { if (value.IsBool()) data = value.GetBool(); }

			void read_single(int& data, rapidjson::Value& value) { if (value.IsInt()) data = value.GetInt(); }

			void read_single(int64_t& data, rapidjson::Value& value) { if (value.IsInt64()) data = value.GetInt64(); }

			void read_single(uint& data, rapidjson::Value& value) { if (value.IsUint()) data = value.GetUint(); }

			void read_single(uint64_t& data, rapidjson::Value& value) { if (value.IsUint64()) data = value.GetUint64(); }

			void read_single(float& data, rapidjson::Value& value) { if (value.IsFloat()) data = value.GetFloat(); }

			void read_single(double& data, rapidjson::Value& value) { if (value.IsDouble()) data = value.GetDouble(); }

			void read_single(vec2& data, rapidjson::Value& value) {
				read_array<glm::vec2, 2>(data, value);
			}
			void read_single(vec3& data, rapidjson::Value& value) {
				read_array<glm::vec3, 3>(data, value);
			}
			void read_single(vec4& data, rapidjson::Value& value) {
				read_array<vec4, 4>(data, value);
			}
			void read_single(quat& data, rapidjson::Value& value) {
				read_array<quat, 4>(data, value);
			}
			void read_single(mat4& data, rapidjson::Value& value) {
				read_array<mat4, 4>(data, value);
			}

			template<typename T>
			void read_vector(vector<T>& data, json::Value& ivalue);
			
			template<typename TKey, typename TVal>
			void read_map(map<TKey, TVal>& data, json::Value& ivalue);

			shared_ptr<Object> load_obj_impl(const std::string& id);

		private:
			hashtable<string, Status> status_table_;
			hashtable<string, shared_ptr<Object>> ref_cache_;
			json::Value real_objs_;
			std::string json_str_;
			fs::path load_file_;
			json::Document doc_;
		};
	}
}

#include "generated/SerializeAll.gen.h"

/**********************************Dump-Load impl**************************************/
namespace staywalk {
	namespace reflect {
		template<typename T>
		void Dumper::write_single(const T& data, rapidjson::Value& value) {
			constexpr bool is_obj = 
				std::is_base_of_v<staywalk::Object, T> || 
				std::is_same_v<T, staywalk::Object> ||
				std::is_same_v<T, staywalk::Transform> ||
				std::is_same_v<T, staywalk::Vertex>;

			constexpr bool is_enum = std::is_enum_v<T>;
			static_assert((is_obj || is_enum) && "other tyep shoubld override in template function");
			if constexpr (is_obj) {
				value.SetObject();
				data.dump(value, *this);
			}
			else {
				write_single(static_cast<const int>(data), value);
			}
		}

		template<typename T>
		void Dumper::write_vector(const vector<T>& data, rapidjson::Value& value) {
			value.SetArray();
			for (const auto& it : data) {
				json::Value item_value;
				this->write(it, item_value);
				value.PushBack(item_value, doc_.GetAllocator());
			}
		}

		template<typename TKey, typename TVal>
		void Dumper::write_map(const map<TKey, TVal>& data, rapidjson::Value& value) {
			value.SetObject();
			for (const auto& it : data) {
				json::Value kvalue(fmt::format("{}", it.first).c_str(), doc_.GetAllocator());
				json::Value vvalue;
				this->write(it.second, vvalue);
				value.AddMember(kvalue, vvalue, doc_.GetAllocator());
			}
		}

		template<typename T, size_t N>
		void Dumper::write_array(const T& data, json::Value& value) {
			value.SetArray();
			for (int i = 0; i < N; i++) {
				json::Value element;
				write_single(data[i], element);
				value.PushBack(element, doc_.GetAllocator());
			}
		}

		template<typename T>
		void Loader::read_single(T& data, json::Value& ivalue) {
			constexpr bool is_obj =
				std::is_base_of_v<staywalk::Object, T> ||
				std::is_same_v<T, staywalk::Object> ||
				std::is_same_v<T, staywalk::Transform> ||
				std::is_same_v<T, staywalk::Vertex>;

			constexpr bool is_enum = std::is_enum_v<T>;
			static_assert((is_obj || is_enum) && "other tyep shoubld override in template function");

			if constexpr (is_obj) {
				data.load(ivalue, *this);
			}
			else {
				int cast_data;
				read_single(cast_data, ivalue);
				data = static_cast<T>(cast_data);
			}
		}

		template<typename T>
		void Loader::read_vector(vector<T>& data, json::Value& ivalue) {
			data.clear();
			if (!ivalue.IsArray()) return;
			auto arr = ivalue.GetArray();
			data.resize(arr.Size());
			for (int i = 0; i < static_cast<int>(arr.Size()); i++)
				read(data[i], arr[i]);
		}

		template<typename TKey, typename TVal>
		void Loader::read_map(map<TKey, TVal>& data, json::Value& ivalue) {
			data.clear();
			if (!ivalue.IsObject()) return;
			for (auto& m : ivalue.GetObject()) {
				TKey k; TVal v;
				std::string strk;
				read(strk, m.name);
				read(v, m.value);
				if constexpr (std::is_same_v<TKey, string>) {
					k = strk;
				}
				else {
					k = (TKey)(std::stoll(strk));
				}
				data.emplace(k, v);
			}
		}

		template<typename T, size_t N>
		void Loader::read_array(T& data, json::Value& value) {
			if (!value.IsArray()) return;
			auto arr = value.GetArray();
			assert(arr.Size() == N);
			for (int i = 0; i < N; i++) 
				read(data[i], value[i]);
		}
	}
}

/************************compareor impl**************************/
// impl
namespace staywalk {
	template<typename T>
	bool Comparer::equal(const T& lhs, const T& rhs) {
		return lhs == rhs;
	}

	template<typename T>
	bool Comparer::equal(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs) {
		if (lhs == nullptr && rhs == nullptr) return true;
		if (lhs && rhs) return Comparer::equal(*lhs, *rhs);
		return false;
	}

	template<typename T>
	bool Comparer::equal(const vector<T>& lhs, const vector<T>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [](const T& a, const T& b) {
			return Comparer::equal(a, b);
			});
	}

	template<typename TK, typename TV>
	bool Comparer::equal(const map<TK, TV>& lhs, const map<TK, TV>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [](const std::pair<TK, TV>& a, const std::pair<TK, TV>& b) {
			return Comparer::equal(a.first, b.first) && Comparer::equal(a.second, b.second);
			});
	}
}

#endif // !_IN_REFLECT
