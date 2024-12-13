#include "Object.h"
#include "GameObject.h"
#include "Actor.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "GameComponent.h"
#include "RMesh.h"
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "Terrain.h"
#include "Animation.h"
#include "Animation.h"
#include "SkeletonMeshComponent.h"
#include "RProgram.h"
#include "RenderInfo.h"
#include "RProgram.h"
#include "RenderObject.h"
#include "Camera.h"
#include "RenderObject.h"
#include "RenderObject.h"



#include "reflect.h"
using namespace staywalk;
shared_ptr<Object> reflect::create_empty(reflect::MetaInfo minfo) {
    if (false) { return nullptr; }

    else if (minfo.tname == "staywalk::Object"){return std::make_shared<::staywalk::Object>();}

    else if (minfo.tname == "staywalk::GameObject"){return std::make_shared<::staywalk::GameObject>();}

    else if (minfo.tname == "staywalk::Actor"){return std::make_shared<::staywalk::Actor>();}

    else if (minfo.tname == "staywalk::RObject"){return std::make_shared<::staywalk::RObject>();}

    else if (minfo.tname == "staywalk::Tex2D"){return std::make_shared<::staywalk::Tex2D>();}

    else if (minfo.tname == "staywalk::CubeMap"){return std::make_shared<::staywalk::CubeMap>();}

    else if (minfo.tname == "staywalk::Shader"){return std::make_shared<::staywalk::Shader>();}

    else if (minfo.tname == "staywalk::Uniform"){return std::make_shared<::staywalk::Uniform>();}

    else if (minfo.tname == "staywalk::Program"){return std::make_shared<::staywalk::Program>();}

    else if (minfo.tname == "staywalk::Material"){return std::make_shared<::staywalk::Material>();}

    else if (minfo.tname == "staywalk::Camera"){return std::make_shared<::staywalk::Camera>();}

    else if (minfo.tname == "staywalk::RLight"){return std::make_shared<::staywalk::RLight>();}

    else if (minfo.tname == "staywalk::GameComponent"){return std::make_shared<::staywalk::GameComponent>();}

    else if (minfo.tname == "staywalk::Mesh"){return std::make_shared<::staywalk::Mesh>();}

    else if (minfo.tname == "staywalk::SkeletonMesh"){return std::make_shared<::staywalk::SkeletonMesh>();}

    else if (minfo.tname == "staywalk::StaticMeshComponent"){return std::make_shared<::staywalk::StaticMeshComponent>();}

    else if (minfo.tname == "staywalk::Terrain"){return std::make_shared<::staywalk::Terrain>();}

    else if (minfo.tname == "staywalk::BoneTreeNode"){return std::make_shared<::staywalk::BoneTreeNode>();}

    else if (minfo.tname == "staywalk::Animation"){return std::make_shared<::staywalk::Animation>();}

    else if (minfo.tname == "staywalk::SkeletonMeshComponent"){return std::make_shared<::staywalk::SkeletonMeshComponent>();}

    else {assert(false); return nullptr;}

}



template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::UniformType>() {
    return { 
        {static_cast<int>(::staywalk::UniformType::U1f), "U1f"},
        {static_cast<int>(::staywalk::UniformType::U2f), "U2f"},
        {static_cast<int>(::staywalk::UniformType::U3f), "U3f"},
        {static_cast<int>(::staywalk::UniformType::U4f), "U4f"},
        {static_cast<int>(::staywalk::UniformType::U1i), "U1i"},
        {static_cast<int>(::staywalk::UniformType::U2i), "U2i"},
        {static_cast<int>(::staywalk::UniformType::U3i), "U3i"},
        {static_cast<int>(::staywalk::UniformType::U4i), "U4i"},
        {static_cast<int>(::staywalk::UniformType::UMat4), "UMat4"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProgramType>() {
    return { 
        {static_cast<int>(::staywalk::ProgramType::PBR), "PBR"},
        {static_cast<int>(::staywalk::ProgramType::Shadow), "Shadow"},
        {static_cast<int>(::staywalk::ProgramType::_Count), "_Count"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>() {
    return { 
        {static_cast<int>(::staywalk::ShaderType::None), "None"},
        {static_cast<int>(::staywalk::ShaderType::VS), "VS"},
        {static_cast<int>(::staywalk::ShaderType::FS), "FS"},
        {static_cast<int>(::staywalk::ShaderType::GS), "GS"},
        {static_cast<int>(::staywalk::ShaderType::CS), "CS"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMinFilter>() {
    return { 
        {static_cast<int>(::staywalk::GlMinFilter::NEAREST), "NEAREST"},
        {static_cast<int>(::staywalk::GlMinFilter::LINEAR), "LINEAR"},
        {static_cast<int>(::staywalk::GlMinFilter::NEAREST_MIPMAP_NEAREST), "NEAREST_MIPMAP_NEAREST"},
        {static_cast<int>(::staywalk::GlMinFilter::LINEAR_MIPMAP_NEAREST), "LINEAR_MIPMAP_NEAREST"},
        {static_cast<int>(::staywalk::GlMinFilter::NEAREST_MIPMAP_LINEAR), "NEAREST_MIPMAP_LINEAR"},
        {static_cast<int>(::staywalk::GlMinFilter::LINEAR_MIPMAP_LINEAR), "LINEAR_MIPMAP_LINEAR"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ProjectType>() {
    return { 
        {static_cast<int>(::staywalk::ProjectType::Persepective), "Persepective"},
        {static_cast<int>(::staywalk::ProjectType::Ortho), "Ortho"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlWrap>() {
    return { 
        {static_cast<int>(::staywalk::GlWrap::CLAMP_TO_EDGE), "CLAMP_TO_EDGE"},
        {static_cast<int>(::staywalk::GlWrap::MIRRORED_REPEAT), "MIRRORED_REPEAT"},
        {static_cast<int>(::staywalk::GlWrap::REPEAT), "REPEAT"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlMagFilter>() {
    return { 
        {static_cast<int>(::staywalk::GlMagFilter::NEAREST), "NEAREST"},
        {static_cast<int>(::staywalk::GlMagFilter::LINEAR), "LINEAR"},
    };
}
