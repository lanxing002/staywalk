#pragma once
#ifndef _IN_REFLECT

#include "Common.gen.h"

namespace staywalk{
	class Object;

	namespace reflect {

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

			template<typename T>
			void write(const T& data, ofstream& ofs);

		private:
			template<typename T>
			void write_basic(const T&, ofstream& ofs);
			template<>
			void write_basic(const string&, ofstream& ofs);
			void write_nested_obj(const shared_ptr<Object> obj, ofstream& ofs);
			template<typename T>
			void write_vector(const vector<T>& data, ofstream& ofs);
			template<typename TKey, typename TVal>
			void write_map(const map<TKey, TVal>& data, ofstream& ofs);
			bool clear();

		private:
			void dump_obj_impl(const shared_ptr<Object> obj);

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
			T read_basic(ifstream& ifs);
			template<>
			string read_basic<string>(ifstream& ifs);
			template<typename T>
			void read_vector(vector<T>& data, ifstream& ifs);
			template<typename TKey, typename TVal>
			void read_map(map<TKey, TVal>& data, ifstream& ifs);
			shared_ptr<Object> read_nested_obj(ifstream& ifs);

		private:
			shared_ptr<Object> load_obj_impl(idtype id);
			hashtable<idtype, Status> status_table_;
			hashtable<idtype, shared_ptr<Object>> ref_cache_;
			fs::path load_path_;
		};

		/**********************************Dump-Load impl**************************************/

		template<typename T>
		void Dumper::write<T>(const T& data, ofstream& ofs) {
			this->write_basic<T>(data, ofs);
		}

		template<>
		void Dumper::write<staywalk::Object>(const Object& data, ofstream& ofs) {
			//this->write_basic<T>(data, ofs);
		}

		template<>
		void Dumper::write<staywalk::Object>(const Object& data, ofstream& ofs) {
			//this->write_basic<T>(data, ofs);
		}

		template<typename T>
		void Dumper::write_basic(const T& data, ofstream& ofs) {
			static_assert(std::is_trivial<T>::value && "must be trivial type");
			ofs.write(reinterpret_cast<const char*>(&data), sizeof data);
			return;
		}

		template<>
		void Dumper::write_basic(const string& str, ofstream& ofs) {
			const auto strlen = str.length();
			ofs.write(reinterpret_cast<const char*>(&strlen), sizeof strlen);
			ofs.write(str.c_str(), strlen);
		}

		template<typename T>
		void Dumper::write_vector(const vector<T>& data, ofstream& ofs) {
			this->write_basic(data.size(), ofs);
			constexpr bool is_basic = std::is_trivial_v<T> || std::is_same_v<T, string>;
			for (const auto& it : data) {
				if constexpr (is_basic) write_basic(it, ofs);
				else write_nested_obj(it, ofs);
			}
		}

		template<typename TKey, typename TVal>
		void Dumper::write_map(const map<TKey, TVal>& data, ofstream& ofs) {
			this->write_basic(data.size(), ofs);
			constexpr bool is_basic = std::is_trivial_v<TVal> || std::is_same_v<TVal, string>;
			for (const auto& it : data) {
				this->write_basic(it.first, ofs);
				if constexpr (is_basic) write_basic(it.second, ofs);
				else write_nested_obj(it.second, ofs);
			}
		}


		template<typename T>
		T Loader::read_basic(ifstream& ifs) {
			static_assert(std::is_trivial<T>::value && "must be trivial type");
			T value;
			ifs.read(reinterpret_cast<char*>(&value), sizeof value);
			return value;
		}

		template<>
		string Loader::read_basic<string>(ifstream& ifs)
		{
			string str;
			auto strlen = str.length();
			ifs.read(reinterpret_cast<char*>(&strlen), sizeof strlen);
			str.resize(strlen);
			ifs.read((str.data()), strlen);
			return str;
		}

		template<typename T>
		void Loader::read_vector(vector<T>& data, ifstream& ifs) {
			data.clear();
			auto num = this->read_basic<size_t>(ifs);
			data.resize(num);
			constexpr bool is_basic = std::is_trivial_v<T> || std::is_same_v<T, string>;
			for (size_t i = 0; i < num; i++) {
				if constexpr (is_basic) data[i] = read_basic<T>(ifs);
				else data[i] = std::dynamic_pointer_cast<T::element_type>(read_nested_obj(ifs));
			}
		}

		template<typename TKey, typename TVal>
		void Loader::read_map(map<TKey, TVal>& data, ifstream& ifs) {
			data.clear();
			auto num = read_basic<typename map<TKey, TVal>::size_type>(ifs);
			constexpr bool is_basic = std::is_trivial_v<TVal> || std::is_same_v<TVal, string>;
			for (size_t i = 0; i < num; i++) {
				auto key = read_basic<TKey>(ifs);
				if constexpr (is_basic) data[key] = read_basic<TVal>(ifs);
				else data[key] = std::dynamic_pointer_cast<TVal::element_type>(read_nested_obj(ifs));
			}
		}

	}
}

namespace staywalk {
namespace reflect {
	template<typename T>
	class Serializer {
	public:
		//static ObjectType get_type_value() { static_assert(false && "Not impl"); }
		//static bool operator==(const T& lhs, const T& rhs) {static_assert(false && "Not impl");}

		static void dump(const T& obj, ofstream& ofs, Dumper& dumper) { static_assert(false && "Not impl"); }
		static void load(T& obj, ifstream& ifs, Loader& loader) { static_assert(false && "Not impl"); }
	};
}
}

namespace staywalk {
	template<>
	void staywalk::reflect::Serializer<staywalk::GameObject>::dump(const staywalk::GameObject& obj, ofstream& ofs, Dumper& dumper) {
		Serializer<Object>::dump(obj, ofs, dumper);
		//dumper.write(obj.location, ofs);
		//dumper.write(obj.scale, ofs);
		//dumper.write(obj.rotation, ofs);
	}
}


#include "SerializeAll.gen.h"

#endif // !_IN_REFLECT
