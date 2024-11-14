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

			/**
			*@brief create a ofstream, and write type info
			*/
			void dump(shared_ptr<Object> obj);

			// wirte data to stream for all type which can serialize
			template<typename T>
			void write(const T& data, ofstream& ofs) { this->write_single<T>(data, ofs); }

			template<typename T>
			void write(const std::vector<T>& data, ofstream& ofs) { this->write_vector<T>(data, ofs); }
			
			template<typename TK, typename TV>
			void write(const std::map<TK, TV>& data, ofstream& ofs) { this->write_map<TK, TV>(data, ofs); }

			template<typename T>
			void write(const std::shared_ptr<T>& obj, ofstream& ofs) { 
				static_assert((std::is_base_of_v<staywalk::Object, T> || std::is_same_v<staywalk::Object, T>) 
					&& "unsupport shared_ptr dump of other type");
				idtype dump_id = obj == nullptr ? kInvalidId : obj->get_guid();
				write(dump_id, ofs);
				if (dump_id != kInvalidId) this->dump_obj_impl(obj);
			}
			// end 
			bool clear();

		private:
			/**
			*@brief create a ofstream, and write type info 
			*/
			void dump_obj_impl(const shared_ptr<Object> obj);

			/**
			*@brief write common type dataread_single
			*/
			template<typename T>
			void write_single(const T&, ofstream& ofs);
			template<typename T>
			void write_vector(const vector<T>& data, ofstream& ofs);
			template<typename TKey, typename TVal>
			void write_map(const map<TKey, TVal>& data, ofstream& ofs);

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

			/**
			*@brief create a ifstream, and read type info
			*/
			shared_ptr<Object> load(idtype id);

			template<typename T>
			void read(T& data, ifstream& ifs) { this->read_single<T>(data, ifs); }

			template<typename T>
			void read(std::vector<T>& data, ifstream& ifs) { this->read_vector<T>(data, ifs); }

			template<typename TK, typename TV>
			void read(std::map<TK, TV>& data, ifstream& ifs) { this->read_map<TK, TV>(data, ifs); }

			template<typename T>
			void read(std::shared_ptr<T>& data, ifstream& ifs) {
				static_assert((std::is_same_v<::staywalk::Object, T> || std::is_base_of_v<staywalk::Object, T>) 
					&& "unsupport shared_ptr load of other type");
				idtype id; read(id, ifs);
				data = (id == kInvalidId) ? nullptr : pcast<T>(load_obj_impl(id));
			}

		private:
			template<typename T>
			void read_single(T& data, ifstream& ifs);

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

#include "generated/SerializeAll.gen.h"

/**********************************Dump-Load impl**************************************/
namespace staywalk {
	namespace reflect {
		template<typename T>
		void Dumper::write_single(const T& data, ofstream& ofs) {
			constexpr bool is_obj = std::is_base_of_v<staywalk::Object, T> || std::is_same_v<T, staywalk::Object>;
			if constexpr (is_obj) {
				data.dump(ofs, *this);
			}
			else{
				static_assert(std::is_trivial<T>::value && "must be trivial type");
				ofs.write(reinterpret_cast<const char*>(&data), sizeof data);
			}
			return;
		}

		template<>
		void Dumper::write_single<string>(const string& str, ofstream& ofs);

		template<>
		void Dumper::write_single(const fs::path& path, ofstream& ofs);

		template<typename T>
		void Dumper::write_vector(const vector<T>& data, ofstream& ofs) {
			this->write(data.size(), ofs);
			for (const auto& it : data) this->write(it, ofs);
		}

		template<typename TKey, typename TVal>
		void Dumper::write_map(const map<TKey, TVal>& data, ofstream& ofs) {
			this->write(data.size(), ofs);
			for (const auto& it : data) {
				this->write(it.first, ofs); 
				this->write(it.second, ofs);
			}
		}

		template<>
		void Loader::read_single<string>(string& str, ifstream& ifs);

		template<>
		void Loader::read_single(fs::path& path, ifstream& ifs);

		template<typename T>
		void Loader::read_single(T& data, ifstream& ifs) {
			constexpr bool is_obj = std::is_base_of_v<staywalk::Object, T> || std::is_same_v<T, staywalk::Object>;
			if constexpr (is_obj) {
				data.load(ifs, *this);
			}
			else {
				static_assert(std::is_trivial<T>::value && "must be trivial type");
				ifs.read(reinterpret_cast<char*>(&data), sizeof data);
			}
		}

		template<typename T>
		void Loader::read_vector(vector<T>& data, ifstream& ifs) {
			data.clear();
			size_t num;
			read(num, ifs);
			data.resize(num);
			for (size_t i = 0; i < num; i++) read(data[i], ifs);
		}

		template<typename TKey, typename TVal>
		void Loader::read_map(map<TKey, TVal>& data, ifstream& ifs) {
			data.clear();
			typename map<TKey, TVal>::size_type map_size;
			read(map_size, ifs);
			for (size_t i = 0; i < map_size; i++) {
				TKey key; 
				read(key, ifs);
				read(data[key], ifs);
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

#endif // !_IN_REFLECT
