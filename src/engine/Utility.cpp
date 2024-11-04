#include "Utility.h"
#include "Logger.h"
#include "RenderObject.h"

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

    int64_t nextid()
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
namespace staywalk {

namespace staywalk{
    const string Utility::kFileExt = "swobj";

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<PRTex> find_material_tex(aiMaterial* mat, aiTextureType type)
    {
        vector<PRTex> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            PRTex tex = std::make_shared<RTex>();
            tex->path = str.C_Str();
            textures.push_back(tex);
        }
        return textures;
    }

    static RMesh construct_mesh(aiMesh* mesh, const aiScene* scene)
    {
        // 1. process mesh
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<PRTex> textures;

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
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // 1. diffuse maps
        vector<PRTex> diffuseMaps = find_material_tex(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<PRTex> specularMaps = find_material_tex(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<PRTex> normalMaps = find_material_tex(material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<PRTex> heightMaps = find_material_tex(material, aiTextureType_AMBIENT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        //return Mesh(vertices, indices, textures);
        return RMesh();
    }


    static void process_node(aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++){
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            construct_mesh(mesh, scene);
            //meshes.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++){
            process_node(node->mChildren[i], scene);
        }
    }

    
    int64_t Utility::GetRandomId(){
        using snowflake_t = snowflake<1534832906275L>;
        static snowflake_t uuid;
        return uuid.nextid();
    }

    bool Utility::check_ifstream(const std::ifstream& fstrm){
        if (!fstrm.is_open()) {
            // TODO: logger error
            return false;
        }

        if (!fstrm.good()) {
            // TODO: logger error
            return false;
        }
        return true;
    }

    bool Utility::check_ofstream(const std::ofstream& fstrm)
    {
        if (!fstrm.is_open()) {
            // TODO: logger error
            return false;
        }

        if (!fstrm.good()) {
            // TODO: logger error
            return false;
        }
        return true;
    }

    void staywalk::Utility::load_model(const string& path){
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        //// check for errors
        //if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        //{
        //    cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        //    return;
        //}
        //// retrieve the directory path of the filepath
        //directory = path.substr(0, path.find_last_of('/'));

        //// process ASSIMP's root node recursively
        //processNode(scene->mRootNode, scene);
    }

    void Dumper::dump_in_file(shared_ptr<Object> obj){
        const long long dump_id = obj->get_guid();
        auto it = status_table_.find(dump_id);
        if (it != status_table_.end()){
            if (it->second == Status::Dumping || it->second == Status::Done)
                return;
        }
        status_table_[dump_id] = Status::Wait;
        std::string name = std::to_string(dump_id);
        ofstream ofs(name + Utility::kFileExt, std::ios::binary | std::ios::trunc);
        auto check_r = Utility::check_ofstream(ofs);
        if (check_r) {
            status_table_[dump_id] = Status::Dumping;
            obj->dump(ofs);
        }
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            log(LogLevel::Error, fmt::format("Assimp import error: %s", importer.GetErrorString()));
            return;
        }
        // retrieve the directory path of the filepath
        RMesh result;
        result.path = path;

        // process ASSIMP's root node recursively
        process_node(scene->mRootNode, scene);
    }


}



