#pragma once
#include "Common.h"
#include "RenderObject.h"
#include <type_traits>


namespace staywalk{
	class World;


	class Utility{
	public:
		static const string kObjExt;
		static const string kWorldExt;

		static idtype get_random_id();

		static bool check_ifstream(const std::ifstream& fstrm);
		
		static bool check_ofstream(const std::ofstream& fstrm);

		static void load_model(const string & path);

		//static fs::path get_exe_dir();

		static fs::path get_resource_dir();

		static fs::path get_shaders_dir();
		
		static fs::path get_textures_dir();

		static fs::path get_objects_dir();

		static fs::path get_worlds_dir();

		static fs::path create_temp_dir();

		template<typename Obj>
		static bool euqals(shared_ptr<Obj> lhs, shared_ptr<Obj> rhs);

		static void dump_world(shared_ptr<World> world);

		static shared_ptr<World> load_world(const std::string& name);
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
		template<typename T>
		void write_basic(const T&, ofstream& ofs);
		template<>
		void write_basic(const string&, ofstream& ofs);
		void write_nested_obj(shared_ptr<Object> obj, ofstream& ofs);
		bool clear();

	private:
		void dump_obj_impl(shared_ptr<Object> obj);

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
		shared_ptr<Object> read_nested_obj(ifstream& ifs);

	private:
		shared_ptr<Object> load_obj_impl(idtype id);
		hashtable<idtype, Status> status_table_;
		hashtable<idtype, shared_ptr<Object>> ref_cache_;
		fs::path load_path_;
	};
}


// impl
namespace staywalk {

	template<typename T>
	bool Utility::euqals(shared_ptr<T> lhs, shared_ptr<T> rhs) {
		if (lhs == nullptr && rhs == nullptr) return true;
		if (lhs && rhs) return lhs->operator==(*rhs);
		return false;
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

}