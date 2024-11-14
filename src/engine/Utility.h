#pragma once
#include "Common.h"
#include "RenderObject.h"
#include "RMesh.h"

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

		/***********************************************/
		/*****************render object*****************/
		/***********************************************/
		static shared_ptr<RTex> make_texture(fs::path path);

		static bool load_tex_resource(shared_ptr<RTex> tex);
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
		/**
		* @brief copy source image file and make texture, if loaded then return cache object
		*/
		PRTex make_tex(fs::path path);

		map<fs::path, PRTex> loaded_texs_;
		vector<PRMesh> meshes_;
		fs::path mesh_name_;
		fs::path load_dir_;
	};
}
