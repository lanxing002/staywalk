#include "Object.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "Material.h"
#include "RMesh.h"
#include "StaticMeshComponent.h"
#include "Actor.h"
#include "Camera.h"
#include "Light.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "RenderObject.h"



#include "reflect.h"
using namespace staywalk;
shared_ptr<Object> reflect::create_empty(reflect::MetaInfo minfo) {
    if (false) { return nullptr; }

    else if (minfo.tname == "staywalk::Object"){return std::make_shared<::staywalk::Object>();}

    else if (minfo.tname == "staywalk::GameObject"){return std::make_shared<::staywalk::GameObject>();}

    else if (minfo.tname == "staywalk::GameComponent"){return std::make_shared<::staywalk::GameComponent>();}

    else if (minfo.tname == "staywalk::Resource"){return std::make_shared<::staywalk::Resource>();}

    else if (minfo.tname == "staywalk::Tex2d"){return std::make_shared<::staywalk::Tex2d>();}

    else if (minfo.tname == "staywalk::RObject"){return std::make_shared<::staywalk::RObject>();}

    else if (minfo.tname == "staywalk::RTex"){return std::make_shared<::staywalk::RTex>();}

    else if (minfo.tname == "staywalk::RShader"){return std::make_shared<::staywalk::RShader>();}

    else if (minfo.tname == "staywalk::RProgram"){return std::make_shared<::staywalk::RProgram>();}

    else if (minfo.tname == "staywalk::RUniform"){return std::make_shared<::staywalk::RUniform>();}

    else if (minfo.tname == "staywalk::Material"){return std::make_shared<::staywalk::Material>();}

    else if (minfo.tname == "staywalk::Mesh"){return std::make_shared<::staywalk::Mesh>();}

    else if (minfo.tname == "staywalk::StaticMeshComponent"){return std::make_shared<::staywalk::StaticMeshComponent>();}

    else if (minfo.tname == "staywalk::Actor"){return std::make_shared<::staywalk::Actor>();}

    else if (minfo.tname == "staywalk::Camera"){return std::make_shared<::staywalk::Camera>();}

    else if (minfo.tname == "staywalk::Light"){return std::make_shared<::staywalk::Light>();}

    else {assert(false); return nullptr;}

}



template<>
std::vector<std::pair<int, std::string>>
staywalk::reflect::get_enum_label<::staywalk::ShaderType>() {
    return { 
        {static_cast<int>(::staywalk::ShaderType::None), "None"},
        {static_cast<int>(::staywalk::ShaderType::VS), "VS"},
        {static_cast<int>(::staywalk::ShaderType::FS), "FS"},
        {static_cast<int>(::staywalk::ShaderType::CS), "CS"},
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
staywalk::reflect::get_enum_label<::staywalk::GlWrap>() {
    return { 
        {static_cast<int>(::staywalk::GlWrap::CLAMP_TO_EDGE), "CLAMP_TO_EDGE"},
        {static_cast<int>(::staywalk::GlWrap::MIRRORED_REPEAT), "MIRRORED_REPEAT"},
        {static_cast<int>(::staywalk::GlWrap::REPEAT), "REPEAT"},
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
