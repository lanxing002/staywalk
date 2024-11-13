#pragma once

#ifndef _IN_REFLECT
//#include "Common.gen.h"
#include "reflect.h"
namespace staywalk{

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
		class Dumper;
		class Loader;

		template<typename T>
		class Serializer {
		public:
			//static ObjectType get_type_value() { static_assert(false && "Not impl"); }
			//static bool operator==(const T& lhs, const T& rhs) {static_assert(false && "Not impl");}

			static void dump(const T& obj, ofstream& ofs, Dumper& dumper); /*{ static_assert(false && "Not impl"); }*/
			static void load(T& obj, ifstream& ifs, Loader& loader); /*{ static_assert(false && "Not impl"); }*/
		};


		class Dumper {
		public:
			enum class Status {
				Wait,
				Dumping,
				Done
			};

			Dumper(fs::path dir);
			Dumper(const Dumper&) = delete;
			Dumper(Dumper&&) = delete;
			Dumper& operator=(const Dumper&) = delete;
			Dumper& operator=(Dumper&&) = delete;

			void dump(shared_ptr<Object> obj);

			// wirte data to stream for all type which can serialize
			template<typename T>
			void write(const T& data, ofstream& ofs) { this->write_basic<T>(data, ofs); }

			template<typename T>
			void write(const std::vector<T>& data, ofstream& ofs) { this->write_vector<T>(data, ofs); }
			
			template<typename TK, typename TV>
			void write(const std::map<TK, TV>& data, ofstream& ofs) { this->write_map<TK, TV>(data, ofs); }

			template<typename T>
			void write(const std::shared_ptr<T>& obj, ofstream& ofs) { 
				static_assert(std::is_base_of_v<staywalk::Object, T> && "unsupport shared_ptr dump of other type");
				idtype dump_id = obj == nullptr ? kInvalidId : obj->get_guid();
				write_basic(dump_id, ofs);
				if (dump_id != kInvalidId) this->dump_obj_impl(obj);
			}
			// end 

		private:
			template<typename T>
			void write_basic(const T&, ofstream& ofs);

			template<typename T>
			void write_vector(const vector<T>& data, ofstream& ofs);
			template<typename TKey, typename TVal>
			void write_map(const map<TKey, TVal>& data, ofstream& ofs);
			bool clear();
			void dump_obj_impl(const shared_ptr<Object> obj);

		private:
			hashtable<idtype, Status> status_table_;
			fs::path tmp_path_;
			fs::path target_path_;
		};

		class Loader {
		public:
			enum class Status {
				Wait,
				Loading,
				Done
			};

			Loader(fs::path dir) : load_path_(dir) {}
			Loader(const Loader&) = delete;
			Loader(Loader&&) = delete;
			Loader& operator=(const Loader&) = delete;
			Loader& operator=(Loader&&) = delete;

			shared_ptr<Object> load(idtype id);

			template<typename T>
			void read(T& data, ifstream& ofs) { this->read_basic<T>(data, ofs); }

			template<typename T>
			void read(std::vector<T>& data, ifstream& ofs) { this->read_vector<T>(data, ofs); }

			template<typename TK, typename TV>
			void read(std::map<TK, TV>& data, ifstream& ofs) { this->read_map<TK, TV>(data, ofs); }

			template<typename T>
			void read(std::shared_ptr<T>& data, ifstream& ifs) {
				static_assert((std::is_same_v<::staywalk::Object, T> || std::is_base_of_v<staywalk::Object, T>) && "unsupport shared_ptr dump of other type");
				idtype id; read_basic<idtype>(id, ifs);
				//return  id == kInvalidId ? nullptr : load_obj_impl(id);
			}

		private:
			template<typename T>
			void read_basic(T& data, ifstream& ifs);
			template<>
			void Loader::read_basic<string>(string& str, ifstream& ifs);

			template<>
			void Loader::read_basic(fs::path& path, ifstream& ifs){
				string pstr; this->read_basic(pstr, ifs);  path = fs::path{ pstr };
			}

			template<typename T>
			void read_vector(vector<T>& data, ifstream& ifs);
			template<typename TKey, typename TVal>
			void read_map(map<TKey, TVal>& data, ifstream& ifs);
			shared_ptr<Object> load_obj_impl(idtype id);

		private:
			hashtable<idtype, Status> status_table_;
			hashtable<idtype, shared_ptr<Object>> ref_cache_;
			fs::path load_path_;
		};
	}
}



/**********************************Dump-Load impl**************************************/
namespace staywalk {
	namespace reflect {
		template<typename T>
		void Dumper::write_basic(const T& data, ofstream& ofs) {
			static_assert(std::is_trivial<T>::value && "must be trivial type");
			ofs.write(reinterpret_cast<const char*>(&data), sizeof data);
			return;
		}

		template<>
		void Dumper::write_basic<string>(const string& str, ofstream& ofs);

		template<>
		void Dumper::write_basic(const fs::path& path, ofstream& ofs);

		template<typename T>
		void Dumper::write_vector(const vector<T>& data, ofstream& ofs) {
			//this->write_basic(data.size(), ofs);
			//constexpr bool is_basic = std::is_trivial_v<T> || std::is_same_v<T, string>;
			//for (const auto& it : data) {
			//	if constexpr (is_basic) write_basic(it, ofs);
			//	else write_nested_obj(it, ofs);
			//}
		}

		template<typename TKey, typename TVal>
		void Dumper::write_map(const map<TKey, TVal>& data, ofstream& ofs) {
			//this->write_basic(data.size(), ofs);
			//constexpr bool is_basic = std::is_trivial_v<TVal> || std::is_same_v<TVal, string>;
			//for (const auto& it : data) {
			//	this->write_basic(it.first, ofs);
			//	if constexpr (is_basic) write_basic(it.second, ofs);
			//	else write_nested_obj(it.second, ofs);
			//}
		}

		template<typename T>
		void Loader::read_basic(T& data, ifstream& ifs) {
			static_assert(std::is_trivial<T>::value && "must be trivial type");
			ifs.read(reinterpret_cast<char*>(&data), sizeof data);
		}

		template<>
		inline void Loader::read_basic(string& str, ifstream& ifs) {
			str.clear();
			auto strlen = str.length();
			ifs.read(reinterpret_cast<char*>(&strlen), sizeof strlen);
			str.resize(strlen);
			ifs.read((str.data()), strlen);
		}

		template<typename T>
		void Loader::read_vector(vector<T>& data, ifstream& ifs) {
			data.clear();
			//auto num = this->read_basic<size_t>(ifs);
			//data.resize(num);
			//constexpr bool is_basic = std::is_trivial_v<T> || std::is_same_v<T, string>;
			//for (size_t i = 0; i < num; i++) {
			//	if constexpr (is_basic) data[i] = read_basic<T>(ifs);
			//	else data[i] = std::dynamic_pointer_cast<T::element_type>(read_nested_obj(ifs));
			//}
		}

		template<typename TKey, typename TVal>
		void Loader::read_map(map<TKey, TVal>& data, ifstream& ifs) {
			data.clear();
			typename map<TKey, TVal>::size_type map_size;
			read_basic<typename map<TKey, TVal>::size_type>(map_size, ifs);
			constexpr bool is_basic = std::is_trivial_v<TVal> || std::is_same_v<TVal, string>;
			for (size_t i = 0; i < map_size; i++) {
				TKey key; read_basic(key, ifs);
				if constexpr (is_basic) data[key] = read_basic<TVal>(ifs);
				//else data[key] = std::dynamic_pointer_cast<TVal::element_type>(read_nested_obj(ifs));
			}
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

#include "generated/SerializeAll.gen.h"
#endif // !_IN_REFLECT
