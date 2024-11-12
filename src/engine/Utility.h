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
}