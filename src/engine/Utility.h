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
struct aiAnimation;
struct aiNodeAnim;

namespace staywalk{
	class World;

	class sw_Class(nogui; nojson;) Utility {
	public:
		static const string kObjExt;
		static const string kMeshExt;
		static const string kSkeletonMeshExt;
		static const string kWorldExt;
		static const string kBoneExt;

		static idtype get_random_id();

		/***********************************************/
		/*******************dump load*******************/
		/***********************************************/
		static bool check_ifstream(const std::ifstream& fstrm);
		
		static bool check_ofstream(const std::ofstream& fstrm);

		//static fs::path get_exe_dir();

		static fs::path get_py_home();

		static fs::path get_resource_dir();

		static fs::path get_deferred_shaders_dir();
		
		static fs::path get_forward_shaders_dir();

		static fs::path get_common_shaders_dir();
		
		static fs::path get_compute_shaders_dir();

		static string get_deferred_vs_tempalte();

		static string get_deferred_fs_template();

		static fs::path get_textures_dir();

		static fs::path get_objects_dir();

		static fs::path get_worlds_dir();

		static fs::path create_temp_dir();

		static fs::path get_script_dir(); 

		static bool load_text(const fs::path& file_name, std::string& text);

		static bool dump_text(const fs::path& file_name, const std::string& text);

		static MeshRef create_simple_triangle();

		static void check_gl_error(const std::string& file_line);

		static void check_fb_completeness(unsigned int glid, const std::string & file_line);

		/***********************************************/
		/*****************render object*****************/
		/***********************************************/
		static shared_ptr<Tex2D> make_texture(fs::path path);

		sw_Func() static shared_ptr<Tex2D> create_tex(string path) { return make_texture(fs::path(path)); }
		sw_Func() static StaticMeshComponentRef create_sm_from_obj(string path, bool flip_uv = true);
		sw_Func() static SkeletonMeshComponentRef create_skeleton_from_obj(string path, bool flip_uv = true);
		//sw_Func() static StaticMeshComponentRef create_sm_from_obj(string path);

		template<typename T>
		static void write_vector_to_ofs(ofstream& ofs, const vector<T>& data);

		template<typename T>
		static void read_vector_from_ifs(ifstream& ofs, vector<T>& data);

		static bool load_tex_resource(Tex2D& tex);

		static bool load_cube_resource(CubeMap& cubemap);


	};

	class MeshLoader
	{
	public:
		MeshLoader(const string& mesh_name, bool flip_uv);
		const vector<pair<MeshRef, MaterialRef>>& get_meshes() { return meshes_; }

	private:
		pair<MeshRef, MaterialRef> construct_mesh(aiMesh* mesh, const aiScene* scene);
		void process_node(aiNode* node, const aiScene* scene);
		shared_ptr<Tex2D> find_material_tex(aiMaterial* mat, aiTextureType type);
		/**
		* @brief copy source image file and make texture, if loaded then return cache object
		*/
		Tex2DRef make_tex(fs::path path);

		map<fs::path, Tex2DRef> loaded_texs_;
		vector<pair<MeshRef, MaterialRef>> meshes_;

		fs::path mesh_name_;
		fs::path load_dir_;
	};


	class SkeletonMeshLoader
	{
		class  BoneInfo {
		public:
			int id_;
			glm::mat4 offset_;

		};

	public:
		SkeletonMeshLoader(const string& mesh_name, bool flip_uv);
		const vector<pair<SkeletonMeshRef, MaterialRef>>& get_skeleton_meshes() { return skeleton_meshes_; }
		const AnimationRef& get_animation() { return animation_; }

	private:
		void set_skin_vertex_default(SkinVertex& v);
		pair<SkeletonMeshRef, MaterialRef> construct_skeleton_mesh(aiMesh* mesh, const aiScene* scene);
		void extract_bone_weight_for_vertices(vector<SkinVertex>& vertices, aiMesh* mesh, const aiScene* scene);
		void process_node(aiNode* node, const aiScene* scene);
		shared_ptr<Tex2D> find_material_tex(aiMaterial* mat, aiTextureType type);
		Tex2DRef make_tex(fs::path path);

		void load_bone(const aiNodeAnim* channel, Bone& bone);
		void read_bone_tree(BoneTreeNode& dest, const aiNode* src);
		void read_missing_bone_data(const aiAnimation* animation);
		void reconstruct_bone_info();

	private:
		vector<pair<SkeletonMeshRef, MaterialRef>> skeleton_meshes_;
		AnimationRef animation_;

		map<fs::path, Tex2DRef> loaded_texs_;
		fs::path mesh_name_;
		fs::path load_dir_;
		map<string, BoneInfo> boneinfo_map_;
		int bone_count_ = 0;
	};
}


namespace staywalk {
	template<typename T>
	static void Utility::write_vector_to_ofs(ofstream& ofs, const vector<T>& data) {
		//static_assert(std::is_trivial_v<T> && "must trivial");
		auto num = data.size();
		ofs.write(reinterpret_cast<const char*>(&num), sizeof(num));
		ofs.write(reinterpret_cast<const char*>(data.data()), num * sizeof(T));
	}

	template<typename T>
	static void Utility::read_vector_from_ifs(ifstream& ifs, vector<T>& data) {
		//static_assert(std::is_trivial_v<T> && "must trivial");
		size_t num = 0;
		ifs.read(reinterpret_cast<char*>(&num), sizeof(num));
		data.resize(num);
		ifs.read(reinterpret_cast<char*>(data.data()), num * sizeof(T));
	}
}