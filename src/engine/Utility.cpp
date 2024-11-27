#include "Utility.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "Actor.h"
#include "Camera.h"
#include "Logger.h"
#include "RenderObject.h"
#include "World.h"
#include "Material.h"
#include "Serialize.h"

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

    shared_ptr<RTex> Utility::make_texture(fs::path tex_name){
        auto result = std::make_shared<RTex>();
        result->tex.name = tex_name.u8string();
        load_tex_resource(*result);
        return result;
    }

    bool Utility::load_tex_resource(RTex& rtex)
    {
        auto path = get_textures_dir() / fs::path(rtex.tex.name);
        if (fs::is_directory(path) || !fs::exists(path)) {
            log(fmt::format("Utility --> load_texture : not find target ({})", path.u8string()), LogLevel::Error);
            return false;
        }

        rtex.tex.data = stbi_load(path.u8string().c_str(),
            &(rtex.tex.width), &(rtex.tex.height), &(rtex.tex.nr_comps), 0);

        if (rtex.tex.data == nullptr) {
            log(fmt::format("Utility --> load_texture : failed when load {}", path.u8string()), LogLevel::Error);
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

    fs::path Utility::get_shaders_dir() {
        return fs::path("resource/shaders");
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

    
    MeshLoader::MeshLoader(const string& mname)
    :mesh_name_(mname){
        if (fs::is_directory(mesh_name_) ||  !fs::exists(mesh_name_)) {
            log(fmt::format("MeshLoader --> mesh ({}) not exists!", mesh_name_.u8string()), LogLevel::Warn);
            return;
        }
        log(fmt::format("MeshLoader --> consturct mesh data from ({})", mesh_name_.u8string()));
        load_dir_ = mesh_name_.parent_path();

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(mesh_name_.u8string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            log(fmt::format("Assimp --> error : {}", importer.GetErrorString()), LogLevel::Error);
            return;
        }
        // retrieve the directory path of the filepath
        process_node(scene->mRootNode, scene);

        vector<PRMesh> merge_meshes;
        for (auto& m : meshes_) {
            bool merged = false;
            for (auto& tm : merge_meshes) {
                if (m->mat->is_same(tm->mat)) {
                    tm->vertices.insert(tm->vertices.end(), m->vertices.begin(), m->vertices.end());
                    tm->indices.insert(tm->indices.end(), m->indices.begin(), m->indices.end());
                    merged = true;
                    break;
                }
            }
            if (!merged) merge_meshes.push_back(m);
        }
        meshes_ = merge_meshes;
    }


    PRMesh MeshLoader::construct_mesh(aiMesh* mesh, const aiScene* scene)
    {
        // 1. process mesh
        vector<Vertex> vertices;
        vector<unsigned int> indices;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            if (mesh->HasNormals())
                vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vertex.texcoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
                vertex.tangent = vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
                vertex.bitangent = vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            }
            else
                vertex.texcoords = vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // 2. process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //TODO: read texs and unforms to consturct staywalk::Material
        PRTex diffuseMaps = find_material_tex(material, aiTextureType_DIFFUSE);
        shared_ptr<Material> mat = std::make_shared<Material>();
        mat->add_tex(Material::DiffuseKey, diffuseMaps);

        auto result = std::make_shared<RMesh>(vertices, indices);
        result->mat = mat;
        return result;
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
    PRTex MeshLoader::find_material_tex(aiMaterial* mat, aiTextureType type)
    {
        if (mat->GetTextureCount(type) > 0) {
            aiString str;
            mat->GetTexture(type, 0, &str);
            fs::path tex_path = load_dir_ / fs::path{ str.C_Str()};
            return make_tex(tex_path);
        }
        return PRTex{ nullptr };
    }

    PRTex MeshLoader::make_tex(fs::path path)
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

        return PRTex(nullptr);
    }

}



