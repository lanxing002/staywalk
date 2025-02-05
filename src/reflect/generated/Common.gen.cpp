#include "Object.h"
#include "Entity.h"
#include "Actor.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "RProgram.h"
#include "StateSet.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "Component.h"
#include "RMesh.h"
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "Terrain.h"
#include "Animation.h"
#include "Animation.h"
#include "SkeletonMeshComponent.h"
#include "RenderTarget.h"
#include "DepthRenderTarget.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/staywalk/src/project/SkyBox.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RProgram.h"
#include "RenderInfo.h"
#include "Camera.h"
#include "RProgram.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "Light.h"



#include "reflect.h"
using namespace staywalk;
shared_ptr<Object> reflect::create_empty(reflect::MetaInfo minfo) {
    if (false) { return nullptr; }

    else if (minfo.tname == "staywalk::Object"){return std::make_shared<::staywalk::Object>();}

    else if (minfo.tname == "staywalk::Entity"){return std::make_shared<::staywalk::Entity>();}

    else if (minfo.tname == "staywalk::Actor"){return std::make_shared<::staywalk::Actor>();}

    else if (minfo.tname == "staywalk::RObject"){return std::make_shared<::staywalk::RObject>();}

    else if (minfo.tname == "staywalk::Tex"){return std::make_shared<::staywalk::Tex>();}

    else if (minfo.tname == "staywalk::Tex2D"){return std::make_shared<::staywalk::Tex2D>();}

    else if (minfo.tname == "staywalk::FrameBuffer"){return std::make_shared<::staywalk::FrameBuffer>();}

    else if (minfo.tname == "staywalk::CubeMap"){return std::make_shared<::staywalk::CubeMap>();}

    else if (minfo.tname == "staywalk::RenderTarget2D"){return std::make_shared<::staywalk::RenderTarget2D>();}

    else if (minfo.tname == "staywalk::Shader"){return std::make_shared<::staywalk::Shader>();}

    else if (minfo.tname == "staywalk::Uniform"){return std::make_shared<::staywalk::Uniform>();}

    else if (minfo.tname == "staywalk::Program"){return std::make_shared<::staywalk::Program>();}

    else if (minfo.tname == "staywalk::StdProgram"){return std::make_shared<::staywalk::StdProgram>();}

    else if (minfo.tname == "staywalk::CSProgram"){return std::make_shared<::staywalk::CSProgram>();}

    else if (minfo.tname == "staywalk::StateSet"){return std::make_shared<::staywalk::StateSet>();}

    else if (minfo.tname == "staywalk::Material"){return std::make_shared<::staywalk::Material>();}

    else if (minfo.tname == "staywalk::Camera"){return std::make_shared<::staywalk::Camera>();}

    else if (minfo.tname == "staywalk::RLight"){return std::make_shared<::staywalk::RLight>();}

    else if (minfo.tname == "staywalk::Component"){return std::make_shared<::staywalk::Component>();}

    else if (minfo.tname == "staywalk::Mesh"){return std::make_shared<::staywalk::Mesh>();}

    else if (minfo.tname == "staywalk::SkeletonMesh"){return std::make_shared<::staywalk::SkeletonMesh>();}

    else if (minfo.tname == "staywalk::StaticMeshComponent"){return std::make_shared<::staywalk::StaticMeshComponent>();}

    else if (minfo.tname == "staywalk::Terrain"){return std::make_shared<::staywalk::Terrain>();}

    else if (minfo.tname == "staywalk::BoneTreeNode"){return std::make_shared<::staywalk::BoneTreeNode>();}

    else if (minfo.tname == "staywalk::Animation"){return std::make_shared<::staywalk::Animation>();}

    else if (minfo.tname == "staywalk::SkeletonMeshComponent"){return std::make_shared<::staywalk::SkeletonMeshComponent>();}

    else if (minfo.tname == "staywalk::RenderTarget"){return std::make_shared<::staywalk::RenderTarget>();}

    else if (minfo.tname == "staywalk::DepthRenderTarget"){return std::make_shared<::staywalk::DepthRenderTarget>();}

    else if (minfo.tname == "staywalk::Skybox"){return std::make_shared<::staywalk::Skybox>();}

    else {assert(false); return nullptr;}

}



template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlTexInternalFormat>() {
    return { 
        {static_cast<int>(::staywalk::GlTexInternalFormat::RED), "RED"},
        {static_cast<int>(::staywalk::GlTexInternalFormat::RG), "RG"},
        {static_cast<int>(::staywalk::GlTexInternalFormat::RGB), "RGB"},
        {static_cast<int>(::staywalk::GlTexInternalFormat::RGBA), "RGBA"},
        {static_cast<int>(::staywalk::GlTexInternalFormat::DEPTH), "DEPTH"},
        {static_cast<int>(::staywalk::GlTexInternalFormat::DEPTHSTENCIL), "DEPTHSTENCIL"},
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
staywalk::reflect::get_enum_label<::staywalk::GlTexFormatType>() {
    return { 
        {static_cast<int>(::staywalk::GlTexFormatType::UBYTE), "UBYTE"},
        {static_cast<int>(::staywalk::GlTexFormatType::BYTE), "BYTE"},
        {static_cast<int>(::staywalk::GlTexFormatType::USHORT), "USHORT"},
        {static_cast<int>(::staywalk::GlTexFormatType::SHORT), "SHORT"},
        {static_cast<int>(::staywalk::GlTexFormatType::UINT), "UINT"},
        {static_cast<int>(::staywalk::GlTexFormatType::INT), "INT"},
        {static_cast<int>(::staywalk::GlTexFormatType::HFLOAT), "HFLOAT"},
        {static_cast<int>(::staywalk::GlTexFormatType::FLOAT), "FLOAT"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::GlTexFormat>() {
    return { 
        {static_cast<int>(::staywalk::GlTexFormat::RED), "RED"},
        {static_cast<int>(::staywalk::GlTexFormat::RG), "RG"},
        {static_cast<int>(::staywalk::GlTexFormat::RGB), "RGB"},
        {static_cast<int>(::staywalk::GlTexFormat::RGBA), "RGBA"},
        {static_cast<int>(::staywalk::GlTexFormat::DEPTH), "DEPTH"},
        {static_cast<int>(::staywalk::GlTexFormat::DEPTHSTENCIL), "DEPTHSTENCIL"},
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
staywalk::reflect::get_enum_label<::staywalk::ProgramType>() {
    return { 
        {static_cast<int>(::staywalk::ProgramType::PBR), "PBR"},
        {static_cast<int>(::staywalk::ProgramType::Shadow), "Shadow"},
        {static_cast<int>(::staywalk::ProgramType::DeferredPBR), "DeferredPBR"},
        {static_cast<int>(::staywalk::ProgramType::DeferredPBRPost), "DeferredPBRPost"},
        {static_cast<int>(::staywalk::ProgramType::_Count), "_Count"},
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
staywalk::reflect::get_enum_label<::staywalk::GlMagFilter>() {
    return { 
        {static_cast<int>(::staywalk::GlMagFilter::NEAREST), "NEAREST"},
        {static_cast<int>(::staywalk::GlMagFilter::LINEAR), "LINEAR"},
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
staywalk::reflect::get_enum_label<::staywalk::RTComp>() {
    return { 
        {static_cast<int>(::staywalk::RTComp::None), "None"},
        {static_cast<int>(::staywalk::RTComp::COLOR), "COLOR"},
        {static_cast<int>(::staywalk::RTComp::DEPTH), "DEPTH"},
        {static_cast<int>(::staywalk::RTComp::STENCIL), "STENCIL"},
        {static_cast<int>(::staywalk::RTComp::COLOR_DEPTH), "COLOR_DEPTH"},
        {static_cast<int>(::staywalk::RTComp::COLOR_DEPTH_STENCIL), "COLOR_DEPTH_STENCIL"},
        {static_cast<int>(::staywalk::RTComp::DEPTH_STENCIL), "DEPTH_STENCIL"},
    };
}

template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::LightType>() {
    return { 
        {static_cast<int>(::staywalk::LightType::Directional), "Directional"},
        {static_cast<int>(::staywalk::LightType::Position), "Position"},
    };
}
