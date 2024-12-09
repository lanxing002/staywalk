#pragma once
#include "Common.h"
#include "SimpleType.h"
#include "Logger.h"

#include <type_traits>
#include <xutility>

struct aiMesh;
struct aiNode;
enum aiTextureType;
struct aiMaterial;
struct aiScene;

namespace staywalk{
	class World;

	class sw_Class(nogui; nojson;) Utility {
	public:
		static const string kObjExt;
		static const string kMeshExt;
		static const string kWorldExt;

		static idtype get_random_id();

		/***********************************************/
		/*******************dump load*******************/
		/***********************************************/
		static bool check_ifstream(const std::ifstream& fstrm);
		
		static bool check_ofstream(const std::ofstream& fstrm);

		//static fs::path get_exe_dir();

		static fs::path get_py_home();

		static fs::path get_resource_dir();

		static fs::path get_shaders_dir();
		
		static fs::path get_textures_dir();

		static fs::path get_objects_dir();

		static fs::path get_worlds_dir();

		static fs::path create_temp_dir();

		static fs::path get_script_dir(); 

		static bool load_text(const fs::path& file_name, std::string& text);

		static bool dump_text(const fs::path& file_name, const std::string& text);

		static MeshRef create_simple_triangle();

		static void check_gl_error(const std::string& file_line);

		/***********************************************/
		/*****************render object*****************/
		/***********************************************/
		static shared_ptr<Tex2D> make_texture(fs::path path);

		sw_Func() static shared_ptr<Tex2D> create_tex(string path) { return make_texture(fs::path(path)); }

		static bool load_tex_resource(Tex2D& tex);
	};

	class MeshLoader
	{
	public:
		MeshLoader(const string& mesh_name);
		const vector<pair<MeshRef, MaterialRef>>& get_meshes() { return meshes_; }

	private:
		pair<MeshRef, MaterialRef> construct_mesh(aiMesh* mesh, const aiScene* scene);
		void process_node(aiNode* node, const aiScene* scene);
		shared_ptr<Tex2D> find_material_tex(aiMaterial* mat, aiTextureType type);
		/**
		* @brief copy source image file and make texture, if loaded then return cache object
		*/
		RTexRef make_tex(fs::path path);

		map<fs::path, RTexRef> loaded_texs_;
		vector<pair<MeshRef, MaterialRef>> meshes_;
		fs::path mesh_name_;
		fs::path load_dir_;
	};
}
