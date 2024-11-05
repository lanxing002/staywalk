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

		static idtype GetRandomId();

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

		template<typename T>
		static void write_to_stream(const T& data, ofstream& ofs);

		template<typename T>
		static T load_from_stream(ifstream& ifs);

		template<>
		static void write_to_stream(const string& data, ofstream& ofs);

		template<>
		static string load_from_stream(ifstream& ifs);

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

		void dump_in_file(shared_ptr<Object> obj);

		bool clear();

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

		shared_ptr<Object> load_in_file(idtype id);

		shared_ptr<Object> load_in_file(idtype id, ObjectType& ot);

	private:
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
	static void Utility::write_to_stream(const T& data, ofstream& ofs) {
		static_assert(std::is_trivial<T>::value && "must be trivial type");
		ofs.write(reinterpret_cast<const char*>(&data), sizeof data);
		return;
	}

	template<typename T>
	T Utility::load_from_stream(ifstream& ifs) {
		static_assert(std::is_trivial<T>::value && "must be trivial type");
		T value;
		ifs.read(reinterpret_cast<const char*>(&value), sizeof value);
		return value;
	}

	template<>
	void Utility::write_to_stream(const string& str, ofstream& ofs) {
		const auto strlen = str.length();
		ofs.write(reinterpret_cast<const char*>(&strlen), sizeof strlen);
		ofs.write(str.c_str(), strlen);
	}

	template<>
	string Utility::load_from_stream(ifstream& ifs)
	{
		string str;
		auto strlen = str.length();
		ifs.read(reinterpret_cast<char*>(&strlen), sizeof strlen);
		str.resize(strlen);
		ifs.read((str.data()), strlen);
		return str;
	}
}