#include "Utility.h"
#include "Entity.h"
#include "Component.h"
#include "Actor.h"
#include "Camera.h"
#include "Logger.h"
#include "RenderObject.h"
#include "World.h"
#include "Material.h"
#include "Serialize.h"
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"
#include "Animation.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

#include <chrono>
#include <stdexcept>
#include <mutex>

class snowflake_nonlock
{
public:
    void lock()
    {
    }
    void unlock()
    {
    }
};

template<int64_t Twepoch, typename Lock = snowflake_nonlock>
class snowflake
{
    using lock_type = Lock;
    static constexpr int64_t TWEPOCH = Twepoch;
    static constexpr int64_t WORKER_ID_BITS = 5L;
    static constexpr int64_t DATACENTER_ID_BITS = 5L;
    static constexpr int64_t MAX_WORKER_ID = (1 << WORKER_ID_BITS) - 1;
    static constexpr int64_t MAX_DATACENTER_ID = (1 << DATACENTER_ID_BITS) - 1;
    static constexpr int64_t SEQUENCE_BITS = 12L;
    static constexpr int64_t WORKER_ID_SHIFT = SEQUENCE_BITS;
    static constexpr int64_t DATACENTER_ID_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS;
    static constexpr int64_t TIMESTAMP_LEFT_SHIFT = SEQUENCE_BITS + WORKER_ID_BITS + DATACENTER_ID_BITS;
    static constexpr int64_t SEQUENCE_MASK = (1 << SEQUENCE_BITS) - 1;

    using time_point = std::chrono::time_point<std::chrono::steady_clock>;

    time_point start_time_point_ = std::chrono::steady_clock::now();
    int64_t start_millsecond_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    int64_t last_timestamp_ = -1;
    int64_t workerid_ = 0;
    int64_t datacenterid_ = 0;
    int64_t sequence_ = 0;
    lock_type lock_;
public:
    snowflake() = default;

    snowflake(const snowflake&) = delete;

    snowflake& operator=(const snowflake&) = delete;

    void init(int64_t workerid, int64_t datacenterid)
    {
        if (workerid > MAX_WORKER_ID || workerid < 0) {
            throw std::runtime_error("worker Id can't be greater than 31 or less than 0");
        }

        if (datacenterid > MAX_DATACENTER_ID || datacenterid < 0) {
            throw std::runtime_error("datacenter Id can't be greater than 31 or less than 0");
        }

        workerid_ = workerid;
        datacenterid_ = datacenterid;
    }

    staywalk::idtype nextid()
    {
        std::lock_guard<lock_type> lock(lock_);
        //std::chrono::steady_clock  cannot decrease as physical time moves forward
        auto timestamp = millsecond();
        if (last_timestamp_ == timestamp)
        {
            sequence_ = (sequence_ + 1) & SEQUENCE_MASK;
            if (sequence_ == 0)
            {
                timestamp = wait_next_millis(last_timestamp_);
            }
        }
        else
        {
            sequence_ = 0;
        }

        last_timestamp_ = timestamp;

        return ((timestamp - TWEPOCH) << TIMESTAMP_LEFT_SHIFT)
            | (datacenterid_ << DATACENTER_ID_SHIFT)
            | (workerid_ << WORKER_ID_SHIFT)
            | sequence_;
    }

private:
    int64_t millsecond() const noexcept
    {
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time_point_);
        return start_millsecond_ + diff.count();
    }

    int64_t wait_next_millis(int64_t last) const noexcept
    {
        auto timestamp = millsecond();
        while (timestamp <= last)
        {
            timestamp = millsecond();
        }
        return timestamp;
    }
};

namespace staywalk{
    const string Utility::kObjExt = ".swobj";
    const string Utility::kWorldExt = ".sworld";
    const string Utility::kMeshExt = ".swmesh";
    const string Utility::kSkeletonMeshExt = ".swsmesh";
    const string Utility::kBoneExt = ".swbone";

	static  glm::mat4 convert_matrix_to_glm(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}

    idtype Utility::get_random_id(){
        using snowflake_t = snowflake<1534832906275L>;
        static snowflake_t uuid;
        return uuid.nextid();
    }

    bool Utility::check_ifstream(const std::ifstream& fstrm){
        if (!fstrm.is_open()) {
            log(fmt::format("cannot open file"), LogLevel::Error);
            return false;
        }

        if (!fstrm.good()) {
            log(fmt::format("file stream in wrong status"), LogLevel::Error);
            return false;
        }
        return true;
    }

    bool Utility::check_ofstream(const std::ofstream& fstrm)
    {
        if (!fstrm.is_open()) {
            log(fmt::format("cannot open file stream"), LogLevel::Error);
            return false;
        }

        if (!fstrm.good()) {
            log( fmt::format("file stream in wrong status"), LogLevel::Error);
            return false;
        }
        return true;
    }

	void Utility::check_gl_error(const std::string& file_line){
        return;
		GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR){
            string info;
            switch (error){
            case GL_INVALID_ENUM:
                info = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                info = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                info = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                info = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                info = "GL_OUT_OF_MEMORY";
                break;
            case GL_STACK_UNDERFLOW:
                info = "GL_STACK_UNDERFLOW";
                break;
            case GL_STACK_OVERFLOW:
                info = "GL_STACK_OVERFLOW";
                break;
            default:
                break;
            }
            log(fmt::format("opengl::error --> {}, {}", info, file_line), LogLevel::Error);
		}
	}

    void Utility::check_fb_completeness(unsigned int glid, const std::string& file_line) {
        glBindFramebuffer(GL_FRAMEBUFFER, glid);
        bool success = true;
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            success = false;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        if (!success)
            log(fmt::format("opengl::framebuffer not complete --> {}", file_line), LogLevel::Error);
    }

	shared_ptr<Tex2D> Utility::make_texture(fs::path tex_name) {
        auto result = std::make_shared<Tex2D>();
        result->name_ = tex_name.stem().u8string();
        result->img_name_ = tex_name.u8string();
        load_tex_resource(*result);
        return result;
    }

	staywalk::StaticMeshComponentRef Utility::create_sm_from_obj(string path, bool flip_uv){
		auto meshload = MeshLoader(path, flip_uv);
		Ref<StaticMeshComponent> sm = std::make_shared<StaticMeshComponent>();
		sm->meshs = meshload.get_meshes();
        return sm;
	}

    SkeletonMeshComponentRef Utility::create_skeleton_from_obj(string path, bool flip_uv) {
        auto meshloader = SkeletonMeshLoader(path, flip_uv);
        SkeletonMeshComponentRef sm = std::make_shared<SkeletonMeshComponent>();
        sm->animation_ = meshloader.get_animation();
        sm->meshs_ = meshloader.get_skeleton_meshes();
        return sm;
    }


	bool Utility::load_tex_resource(Tex2D& rtex) {
        auto path = get_textures_dir() / fs::path(rtex.img_name_);
        if (fs::is_directory(path) || !fs::exists(path)) {
            log(fmt::format("Utility --> load_texture : not find target ({})", path.u8string()), LogLevel::Error);
            return false;
        }
        stbi_set_flip_vertically_on_load(true);
        rtex.host_data_ = stbi_load(path.u8string().c_str(),
            &(rtex.width_), &(rtex.height_), &(rtex.nr_comps_), 0);

        if (rtex.host_data_ == nullptr) {
            log(fmt::format("Utility --> load_texture : failed when load {}", path.u8string()), LogLevel::Error);
            return false;
        }
        return true;
    }

	bool Utility::load_cube_resource(CubeMap& cubemap){
        auto path = get_textures_dir() / "cubemap" / fs::path(cubemap.img_name_);
        auto file_name = path.u8string() + "-nx." + cubemap.img_extension_;
        int width = 0, height = 0, nrcomps = 0;
        int width_cmp = 0, height_cmp = 0, nrcomps_cmp = 0;
		cubemap.host_data_nx_ = stbi_load(file_name.c_str(), &(width), &(height), &(nrcomps), 0);
        width_cmp = width;
        height_cmp = height;
        nrcomps_cmp = nrcomps;

		file_name = path.u8string() + "-ny." + cubemap.img_extension_;
		cubemap.host_data_ny_ = stbi_load(file_name.c_str(), &(width), &(height), &(nrcomps), 0);
        assert(width_cmp == width && height_cmp == height && nrcomps == nrcomps_cmp);

		file_name = path.u8string() + "-nz." + cubemap.img_extension_;
		cubemap.host_data_nz_ = stbi_load(file_name.c_str(), &(width), &(height), &(nrcomps), 0);
        assert(width_cmp == width && height_cmp == height && nrcomps == nrcomps_cmp);

		file_name = path.u8string() + "-px." + cubemap.img_extension_;
		cubemap.host_data_px_ = stbi_load(file_name.c_str(), &(width), &(height), &(nrcomps), 0);
        assert(width_cmp == width && height_cmp == height && nrcomps == nrcomps_cmp);

		file_name = path.u8string() + "-py." + cubemap.img_extension_;
		cubemap.host_data_py_ = stbi_load(file_name.c_str(), &(width), &(height), &(nrcomps), 0);
        assert(width_cmp == width && height_cmp == height && nrcomps == nrcomps_cmp);

		file_name = path.u8string() + "-pz." + cubemap.img_extension_;
		cubemap.host_data_pz_ = stbi_load(file_name.c_str(), &(width), &(height), &(nrcomps), 0);
        assert(width_cmp == width && height_cmp == height && nrcomps == nrcomps_cmp);

        cubemap.width_ = width;
        cubemap.height_ = height;
        cubemap.nr_comps_ = nrcomps;
		if (cubemap.host_data_nx_ == nullptr
            || cubemap.host_data_ny_ == nullptr
			|| cubemap.host_data_nz_ == nullptr
			|| cubemap.host_data_px_ == nullptr
			|| cubemap.host_data_py_ == nullptr
			|| cubemap.host_data_pz_ == nullptr
            ) {
			log(fmt::format("Utility --> load_cubemap : failed when load {}", file_name), LogLevel::Error);
			return false;
		}
        return true;
	}

	fs::path Utility::get_py_home() {
        return fs::absolute(fs::path("3rdparty/cpython/build"));
    }

    fs::path Utility::get_resource_dir() {
        return fs::path("resource");
    }

    fs::path Utility::get_deferred_shaders_dir() {
        return fs::path("resource/shaders/deferred");
    }

    fs::path Utility::get_forward_shaders_dir() {
        return fs::path("resource/shaders/forward");
    }

    fs::path Utility::get_common_shaders_dir() {
        return fs::path("resource/shaders/common");
    }

    string Utility::get_deferred_vs_tempalte() {
        string result;
        if (result.size() == 0) {
            fs::path name = get_common_shaders_dir() / "deferred_common.vs";
            assert(fs::exists(name));
            ifstream ifs(name, std::ios::in);
            result = string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            //assert(result.size() > 0);
        }

        return result;
    }

    string Utility::get_deferred_fs_template() {
        string result;
        if (result.size() == 0) {
            fs::path name = get_common_shaders_dir() / "deferred_common.fs";
            assert(fs::exists(name));
            ifstream ifs(name, std::ios::in);
            result = string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            //assert(result.size() > 0);
        }

        return result;
    }

    fs::path Utility::get_textures_dir() {
        return fs::path("resource/textures");
    }

    fs::path Utility::get_objects_dir() {
        return fs::path("resource/objects");
    }

    fs::path Utility::get_worlds_dir()
    {
        return fs::path("resource/worlds");
    }

    fs::path Utility::create_temp_dir() {
        using snowflake_t = snowflake<153406275L>;
        static snowflake_t uuid;

        fs::path tmp_path = fs::temp_directory_path() / std::to_string(uuid.nextid());
        while (fs::exists(tmp_path)){
            tmp_path = fs::temp_directory_path() / std::to_string(uuid.nextid());
        }
        fs::create_directory(tmp_path);
        return tmp_path;
    }

    
	staywalk::fs::path Utility::get_script_dir()
	{
		return fs::path("resource/script");
	}

	bool Utility::load_text(const fs::path& file_name, std::string& text){
        if (!fs::exists(file_name)) return false;

		ifstream ifs = ifstream(file_name, std::ios::in);
		if (!ifs) return false;
		std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        text = content;
        return true;
	}

	bool Utility::dump_text(const fs::path& file_name, const std::string& text){
        ofstream ofs = ofstream(file_name, std::ios::out | std::ios::trunc);
        if (!ofs) return false;
        ofs.write(text.c_str(), text.size());
        return static_cast<bool>(ofs);
	}

	MeshLoader::MeshLoader(const string& mname, bool flip_uv)
    :mesh_name_(mname){
        if (fs::is_directory(mesh_name_) ||  !fs::exists(mesh_name_)) {
            log(fmt::format("MeshLoader --> mesh ({}) not exists!", mesh_name_.u8string()), LogLevel::Warn);
            return;
        }
        log(fmt::format("MeshLoader --> consturct mesh data from ({})", mesh_name_.u8string()));
        load_dir_ = mesh_name_.parent_path();

        Assimp::Importer importer;
		auto flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals /*| aiProcess_FlipUVs */ | aiProcess_CalcTangentSpace;
		if (flip_uv) flags |= aiProcess_FlipUVs;
        const aiScene* scene = importer.ReadFile(mesh_name_.u8string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            log(fmt::format("Assimp --> error : {}", importer.GetErrorString()), LogLevel::Error);
            return;
        }
        // retrieve the directory path of the filepath
        process_node(scene->mRootNode, scene);

        vector<pair<MeshRef, MaterialRef>> merge_meshes;
        for (auto& [mesh, mat] : meshes_) {
            bool merged = false;
            for (auto& [tmesh, tmat] : merge_meshes) {
                if (mat->is_same(tmat)) {
                    tmesh->vertices_.insert(tmesh->vertices_.end(), mesh->vertices_.begin(), mesh->vertices_.end());
                    const auto last_size = (uint)tmesh->indices_.size();
                    for (auto& ii : mesh->indices_) ii += last_size;
                    tmesh->indices_.insert(tmesh->indices_.end(), mesh->indices_.begin(), mesh->indices_.end());
                    merged = true;
                    break;
                }
            }
            if (!merged) merge_meshes.emplace_back(mesh, mat);
        }
        meshes_ = merge_meshes;

        for (auto& [mesh, mat] : meshes_) {
            if (mesh) mesh->compute_aabb();
        }
    }


    pair<MeshRef, MaterialRef> MeshLoader::construct_mesh(aiMesh* mesh, const aiScene* scene)
    {
        // 1. process mesh
        vector<Vertex> vertices;
        vector<unsigned int> indices;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.position_ = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            if (mesh->HasNormals())
                vertex.normal_ = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vertex.texcoords_ = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
                vertex.tangent_ = vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
                vertex.bitangent_ = vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            }
            else
                vertex.texcoords_ = vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // 2. process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //TODO: read texs and unforms to consturct staywalk::Material
        Tex2DRef diffuseMaps = find_material_tex(material, aiTextureType_DIFFUSE);
        shared_ptr<Material> mat = std::make_shared<Material>();
        mat->add_tex(Material::DiffuseKey, diffuseMaps);

        auto result = std::make_shared<Mesh>(vertices, indices);
        return {result, mat};
    }

	void MeshLoader::process_node(aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            auto a_mesh = construct_mesh(mesh, scene);
            meshes_.push_back(a_mesh);
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            process_node(node->mChildren[i], scene);
        }
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
    Tex2DRef MeshLoader::find_material_tex(aiMaterial* mat, aiTextureType type)
    {
        if (mat->GetTextureCount(type) > 0) {
            aiString str;
            mat->GetTexture(type, 0, &str);
            fs::path tex_path = load_dir_ / fs::path{ str.C_Str()};
            return make_tex(tex_path);
        }
        return Tex2DRef{ nullptr };
    }

    Tex2DRef MeshLoader::make_tex(fs::path path)
    {
        auto it = loaded_texs_.find(path);
        if(it != loaded_texs_.end()) return it->second;

        if (!fs::exists(path)) {
            log(fmt::format("MeshLoader::make_tex cannot find target texture file: {}", path.u8string()), LogLevel::Warn);
            return nullptr; 
        }

        auto tex_name = path.stem();
        auto tex_extension = path.extension();
        auto new_tex_name = tex_name.u8string() + std::to_string(0) + tex_extension.u8string();
        for (int i = 1; i < 1e8; i++) {
            fs::path new_path = Utility::get_textures_dir() / new_tex_name;
            if (!fs::exists(new_path)) {
                break;
            }
            new_tex_name = tex_name.u8string() + std::to_string(i) + tex_extension.u8string();
        }

        if (fs::copy_file(path, Utility::get_textures_dir() / new_tex_name)){
            auto result = Utility::make_texture(new_tex_name);
            loaded_texs_[path] = result;
            return result;
        }

        return Tex2DRef(nullptr);
    }

	SkeletonMeshLoader::SkeletonMeshLoader(const string& mesh_name, bool flip_uv)
    :mesh_name_(mesh_name){
		if (fs::is_directory(mesh_name_) || !fs::exists(mesh_name_)) {
			log(fmt::format("SkeletonMeshLoader --> mesh ({}) not exists!", mesh_name_.u8string()), LogLevel::Warn);
			return;
		}
		log(fmt::format("SkeletonMeshLoader --> consturct mesh data from ({})", mesh_name_.u8string()));
		load_dir_ = mesh_name_.parent_path();
		auto sname = mesh_name_.stem().u8string();

		Assimp::Importer importer;
        auto flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals /*| aiProcess_FlipUVs */ | aiProcess_CalcTangentSpace;
        if (flip_uv) flags |= aiProcess_FlipUVs;
		const aiScene* scene = importer.ReadFile(mesh_name_.u8string(), flags);

		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			log(fmt::format("Assimp --> error : {}", importer.GetErrorString()), LogLevel::Error);
			return;
		}
		// retrieve the directory path of the filepath
		process_node(scene->mRootNode, scene);

		vector<pair<SkeletonMeshRef, MaterialRef>> merge_meshes;
		for (auto& [mesh, mat] : skeleton_meshes_) {
			bool merged = false;
			for (auto& [tmesh, tmat] : merge_meshes) {
				if (mat->is_same(tmat)) {
					tmesh->vertices_.insert(tmesh->vertices_.end(), mesh->vertices_.begin(), mesh->vertices_.end());
					const auto last_size = (uint)tmesh->indices_.size();
					for (auto& ii : mesh->indices_) ii += last_size;
					tmesh->indices_.insert(tmesh->indices_.end(), mesh->indices_.begin(), mesh->indices_.end());
					merged = true;
					break;
				}
			}
			if (!merged) merge_meshes.emplace_back(mesh, mat);
		}

        skeleton_meshes_ = merge_meshes;
		//for (auto& [mesh, mat] : skeleton_meshes_) {
		//	//if (mesh) mesh->compute_aabb();
		//}

        /****************************/
        {
			animation_ = std::make_shared<Animation>(sname);
			auto animation = scene->mAnimations[0];
			animation_->duration_ = (float)animation->mDuration / 1000.0f;
			animation_->ticks_pers_ = (float)animation->mTicksPerSecond / 1000.0f;
			aiMatrix4x4 g_transform = scene->mRootNode->mTransformation;
			g_transform = g_transform.Inverse();
			read_missing_bone_data(animation);
            read_bone_tree(animation_->node_root_, scene->mRootNode);
            reconstruct_bone_info();
        }
	}

	void SkeletonMeshLoader::set_skin_vertex_default(SkinVertex& v){
		for (int i = 0; i < kMaxBoueInfluence; i++) {
			v.bone_ids_[i] = -1;
			v.bone_weights_[i] = 0.0f;
		}
	}

	staywalk::pair<staywalk::SkeletonMeshRef, staywalk::MaterialRef> SkeletonMeshLoader::construct_skeleton_mesh(aiMesh* mesh, const aiScene* scene){
		// 1. process mesh
		vector<SkinVertex> vertices;
		vector<unsigned int> indices;

		// walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			SkinVertex vertex;
			set_skin_vertex_default(vertex);
			vertex.position_ = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			if (mesh->HasNormals())
				vertex.normal_ = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			if (mesh->mTextureCoords[0]) {
				vertex.texcoords_ = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
				vertex.tangent_ = vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
				vertex.bitangent_ = vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			}
			else
				vertex.texcoords_ = vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		extract_bone_weight_for_vertices(vertices, mesh, scene);

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		Tex2DRef diffuseMaps = find_material_tex(material, aiTextureType_DIFFUSE);
		shared_ptr<Material> mat = std::make_shared<Material>();
		mat->add_tex(Material::DiffuseKey, diffuseMaps);

		auto result = std::make_shared<SkeletonMesh>(vertices, indices);
		return { result, mat };
	}

	void SkeletonMeshLoader::extract_bone_weight_for_vertices(vector<SkinVertex>& vertices, aiMesh* mesh, const aiScene* scene){
		for (uint idx = 0; idx < mesh->mNumBones; ++idx){
			int bone_id = -1;
			std::string boneName = mesh->mBones[idx]->mName.C_Str();
			if (boneinfo_map_.find(boneName) == boneinfo_map_.end()) {
				BoneInfo new_info;
				new_info.id_ = bone_count_;
				new_info.offset_ = convert_matrix_to_glm(mesh->mBones[idx]->mOffsetMatrix);
				boneinfo_map_[boneName] = new_info;
				bone_id = bone_count_;
				bone_count_++;
			}
			else
				bone_id = boneinfo_map_[boneName].id_;
			assert(bone_id != -1);

			auto weights = mesh->mBones[idx]->mWeights;
			int num_weight = mesh->mBones[idx]->mNumWeights;

			for (int widx = 0; widx < num_weight; ++widx) {
				int vertex_id = weights[widx].mVertexId;
				float weight = weights[widx].mWeight;
				assert(vertex_id <= vertices.size());

				for (int i = 0; i < kMaxBoueInfluence; ++i) {
					if (vertices[vertex_id].bone_ids_[i] < 0) {
						vertices[vertex_id].bone_weights_[i] = weight;
						vertices[vertex_id].bone_ids_[i] = bone_id;
						break;
					}
				}
			}
		}
	}

	void SkeletonMeshLoader::process_node(aiNode* node, const aiScene* scene){
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			auto a_mesh = construct_skeleton_mesh(mesh, scene);
			skeleton_meshes_.push_back(a_mesh);
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++) 
			process_node(node->mChildren[i], scene);
	}

	staywalk::shared_ptr<staywalk::Tex2D> SkeletonMeshLoader::find_material_tex(aiMaterial* mat, aiTextureType type){
		if (mat->GetTextureCount(type) > 0) {
			aiString str;
			mat->GetTexture(type, 0, &str);
			fs::path tex_path = load_dir_ / fs::path{ str.C_Str() };
			return make_tex(tex_path);
		}
		return Tex2DRef{ nullptr };
	}

	staywalk::Tex2DRef SkeletonMeshLoader::make_tex(fs::path path){
		auto it = loaded_texs_.find(path);
		if (it != loaded_texs_.end()) return it->second;

		if (!fs::exists(path)) {
			log(fmt::format("MeshLoader::make_tex cannot find target texture file: {}", path.u8string()), LogLevel::Warn);
			return nullptr;
		}

		auto tex_name = path.stem();
		auto tex_extension = path.extension();
		auto new_tex_name = tex_name.u8string() + std::to_string(0) + tex_extension.u8string();
		for (int i = 1; i < 1e8; i++) {
			fs::path new_path = Utility::get_textures_dir() / new_tex_name;
			if (!fs::exists(new_path)) {
				break;
			}
			new_tex_name = tex_name.u8string() + std::to_string(i) + tex_extension.u8string();
		}

		if (fs::copy_file(path, Utility::get_textures_dir() / new_tex_name)) {
			auto result = Utility::make_texture(new_tex_name);
			loaded_texs_[path] = result;
			return result;
		}

		return Tex2DRef(nullptr);
	}

	void SkeletonMeshLoader::load_bone(const aiNodeAnim* channel, Bone& bone) {
		auto num_pos = channel->mNumPositionKeys;
		for (uint i = 0; i < num_pos; i++) {
			aiVector3D ai_pos = channel->mPositionKeys[i].mValue;
			float timeStamp = (float)channel->mPositionKeys[i].mTime / 1000.0f;
			bone.positions_.emplace_back(vec3(ai_pos.x, ai_pos.y, ai_pos.z), timeStamp);
		}

		auto num_rot = channel->mNumRotationKeys;
		for (uint i = 0; i < num_rot; ++i) {
			aiQuaternion ai_rot = channel->mRotationKeys[i].mValue;
			float timeStamp = (float)channel->mRotationKeys[i].mTime / 1000.0f;
			bone.rotations_.emplace_back(quat(ai_rot.w, ai_rot.x, ai_rot.y, ai_rot.z), timeStamp);
		}

		auto num_scale = channel->mNumScalingKeys;
		for (uint i = 0; i < num_scale; ++i) {
			aiVector3D ai_scale = channel->mScalingKeys[i].mValue;
			float timeStamp = (float)channel->mScalingKeys[i].mTime / 1000.0f;
			bone.scales_.emplace_back(vec3(ai_scale.x, ai_scale.y, ai_scale.z), timeStamp);
		}
	}

	void SkeletonMeshLoader::read_bone_tree(BoneTreeNode& dest, const aiNode* src) {
		if (!src) return;

		dest.name_ = std::string(src->mName.data);
		dest.transform_ = convert_matrix_to_glm(src->mTransformation);
        auto it = boneinfo_map_.find(dest.name_);
        if (it == boneinfo_map_.end()) dest.bone_id_ = -1;
        else dest.bone_id_ = it->second.id_;

		for (uint i = 0; i < src->mNumChildren; i++) {
			BoneTreeNode newData;
			read_bone_tree(newData, src->mChildren[i]);
			dest.children_.push_back(newData);
		}
	}

	void SkeletonMeshLoader::read_missing_bone_data(const aiAnimation* animation) {
		int size = animation->mNumChannels;
        auto bone_num = (int)boneinfo_map_.size();
		for (int i = 0; i < size; i++) {
			auto channel = animation->mChannels[i];
			string bone_name = channel->mNodeName.data;
			if (boneinfo_map_.find(bone_name) == boneinfo_map_.end()) {
                boneinfo_map_[bone_name].id_ = bone_num;
				bone_num++;
			}
			Bone bone;
			bone.id_ = boneinfo_map_[bone_name].id_;
			load_bone(channel, bone);
			animation_->bones_.push_back(bone);
		}
	}

	void SkeletonMeshLoader::reconstruct_bone_info(){
        auto bone_num = boneinfo_map_.size();
        assert(bone_num <= kMaxBoneNum);
        vector<Bone> bones(bone_num);

		for (auto& bone : animation_->bones_) bones[bone.id_] = bone;
        for (auto& [n, offset] : boneinfo_map_) bones[offset.id_].offset_ = offset.offset_;
        animation_->bones_ = bones;
	}

}



