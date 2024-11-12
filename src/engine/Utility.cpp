#include "Utility.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "Actor.h"
#include "Camera.h"
#include "Logger.h"
#include "RenderObject.h"
#include "World.h"
#include "Material.h"

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

#include <chrono>
#include <stdexcept>
#include <mutex>

#include "ReflectTemplate.h"


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

    idtype Utility::get_random_id(){
        using snowflake_t = snowflake<1534832906275L>;
        static snowflake_t uuid;
        return uuid.nextid();
    }

    bool Utility::check_ifstream(const std::ifstream& fstrm){
        if (!fstrm.is_open()) {
            log(LogLevel::Error, fmt::format("cannot open file"));
            return false;
        }

        if (!fstrm.good()) {
            log(LogLevel::Error, fmt::format("file stream in wrong status"));
            return false;
        }
        return true;
    }

    bool Utility::check_ofstream(const std::ofstream& fstrm)
    {
        if (!fstrm.is_open()) {
            log(LogLevel::Error, fmt::format("cannot open file stream"));
            return false;
        }

        if (!fstrm.good()) {
            log(LogLevel::Error, fmt::format("file stream in wrong status"));
            return false;
        }
        return true;
    }

    void Utility::dump_world(shared_ptr<World> world){
        if (nullptr == world) return;
        //auto world_file = Utility::get_worlds_dir() / (world->get_name() + Utility::kWorldExt);
        //ofstream ofs(world_file, std::ios::out | std::ios::binary | std::ios::trunc);
        //auto check_r = Utility::check_ofstream(ofs);
        //auto actors = world->get_all_actors();
        //auto dumper = Dumper(Utility::get_objects_dir());
        //dumper.write_basic(actors.size(), ofs);
        //for (auto actor : actors) {
        //    if (nullptr == actor) continue;
        //    //idtype dumpid = actor->get_guid();
        //    //dumper.write_basic(actor->get_guid(), ofs);
        //    dumper.dump(actor);
        //}
        //dumper.clear();
        //ofs.close();
    }

    shared_ptr<World> Utility::load_world(const std::string& name)
    {
        auto world_file = Utility::get_worlds_dir() / (name + Utility::kWorldExt);
        if (!fs::exists(world_file)) {
            log(LogLevel::Error, fmt::format("cannot open world file: {}", fs::absolute(world_file).u8string()));
            return nullptr;
        }

        //ifstream ifs(world_file, std::ios::in | std::ios::binary);
        //auto check_r = Utility::check_ifstream(ifs);
        //auto loader = Loader(Utility::get_objects_dir());
        //vector<idtype> objids;
        //if (check_r) {
        //    size_t num = loader.read_basic<std::size_t>(ifs);
        //    for (size_t i = 0; i < num; i++) {
        //        idtype id = loader.read_basic<idtype>(ifs);
        //        objids.push_back(id);
        //    }
        //}

        shared_ptr<World> world = std::make_shared<World>();
        //for (auto id : objids) {
        //    auto obj = loader.load(id);
        //    //ObjectType ot = obj->get_type_value();

        //    //switch (ot)
        //    //{
        //    //case staywalk::ObjectType::Actor:
        //    //    world->add_actor(std::dynamic_pointer_cast<Actor>(obj));
        //    //    break;
        //    //case staywalk::ObjectType::Camera:
        //    //    break;
        //    //default:
        //    //    break;
        //    //}
        //}

        //world->set_name(name);
        return world;
    }

    shared_ptr<RTex> Utility::load_texture(fs::path path)
    {
        if (fs::is_directory(path) || !fs::exists(path)) {
            log(LogLevel::Error, fmt::format("Utility --> load_texture : not find target ({})", path.u8string()));
            return nullptr;
        }

        /*int width, height, nrComponents;
        unsigned char* data = stbi_load(path.u8string().c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }*/
        
        //stbi_image_free(data);
        return shared_ptr<RTex>();
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

    
    MeshLoader::MeshLoader(const string& mesh_name){
        auto path = fs::path(mesh_name);
        if (fs::is_directory(path) ||  !fs::exists(path)) {
            log(LogLevel::Warining, fmt::format("MeshLoader --> mesh ({}) not exists!", path.u8string()));
            return;
        }
        log(LogLevel::Info, fmt::format("MeshLoader --> consturct mesh data from ({})", path.u8string()));

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path.u8string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            log(LogLevel::Error, fmt::format("Assimp --> error : {}", importer.GetErrorString()));
            return;
        }
        // retrieve the directory path of the filepath
        work_dir_ = path.parent_path();
        process_node(scene->mRootNode, scene);
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
        //result->set_mat(mat);
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
            fs::path p{str.C_Str()};
            return Utility::load_texture(p);
        }
        return PRTex{ nullptr };
    }

}



