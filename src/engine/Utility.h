#pragma once
#include "Common.h"
#include "RenderObject.h"
#include <type_traits>
#include <assimp/scene.h>
#include <xutility>

namespace staywalk{
	class World;

	class Utility{
	public:
		static const string kObjExt;
		static const string kWorldExt;

		static idtype get_random_id();


		/***********************************************/
		/*******************dump load*******************/
		/***********************************************/
		static bool check_ifstream(const std::ifstream& fstrm);
		
		static bool check_ofstream(const std::ofstream& fstrm);

		//static fs::path get_exe_dir();

		static fs::path get_resource_dir();

		static fs::path get_shaders_dir();
		
		static fs::path get_textures_dir();

		static fs::path get_objects_dir();

		static fs::path get_worlds_dir();

		static fs::path create_temp_dir();

		template<typename T>
		static bool equal(const T& lhs, const T& rhs);

		template<typename T>
		static bool equal(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs);

		template<typename T> // vector
		static bool equal(const vector<T>& lhs, const vector<T>& rhs);

		template<typename TK, typename TV> // map
		static bool equal(const map<TK, TV>& lhs, const map<TK, TV>& rhs);

		static void dump_world(shared_ptr<World> world);

		static shared_ptr<World> load_world(const std::string& name);


		/***********************************************/
		/*****************render object*****************/
		/***********************************************/
		static shared_ptr<RTex> load_texture(fs::path path);

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

	class MeshLoader
	{
	public:
		MeshLoader(const string& mesh_name);
		const vector<PRMesh>& get_meshes() { return meshes_; }

	private:
		PRMesh construct_mesh(aiMesh* mesh, const aiScene* scene);
		void process_node(aiNode* node, const aiScene* scene);
		shared_ptr<RTex> find_material_tex(aiMaterial* mat, aiTextureType type);


		vector<PRMesh> meshes_;
		fs::path mesh_name_;
		fs::path work_dir_;
	};
}


// impl
namespace staywalk {
	template<typename T>
	bool Utility::equal(const T& lhs, const T& rhs) {
		return lhs == rhs;
	}

	template<typename T>
	bool Utility::equal(const shared_ptr<T>& lhs, const shared_ptr<T>& rhs) {
		if (lhs == nullptr && rhs == nullptr) return true;
		if (lhs && rhs) return lhs->operator==(*rhs);
		return false;
	}

	template<typename T>
	bool Utility::equal(const vector<T>& lhs, const vector<T>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [](const T& a, const T& b) {
			return Utility::equal(a, b);
			});
	}

	template<typename TK, typename TV>
	bool Utility::equal(const map<TK, TV>& lhs, const map<TK, TV>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), [](const std::pair<TK, TV>& a, const std::pair<TK, TV>& b) {
			return Utility::equal(a.first, b.first) && Utility::equal(a.second, b.second);
			});
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
		for(size_t i = 0; i < num; i++){
			auto key = read_basic<TKey>(ifs);
			if constexpr (is_basic) data[key] = read_basic<TVal>(ifs);
			else data[key] = std::dynamic_pointer_cast<TVal::element_type>(read_nested_obj(ifs));
		}
	}

}