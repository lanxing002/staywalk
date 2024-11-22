#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Object.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\GameObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\GameComponent.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Material.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RMesh.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\StaticMeshComponent.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Actor.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Camera.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Light.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"



#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src\reflect\reflect.h"
using namespace staywalk;
shared_ptr<Object> reflect::create_empty(reflect::MetaInfo minfo) {
    if (false) { return nullptr; }

    else if (minfo.tname == "staywalk::Object"){return std::make_shared<::staywalk::Object>();}

    else if (minfo.tname == "staywalk::GameObject"){return std::make_shared<::staywalk::GameObject>();}

    else if (minfo.tname == "staywalk::GameComponent"){return std::make_shared<::staywalk::GameComponent>();}

    else if (minfo.tname == "staywalk::Resource"){return std::make_shared<::staywalk::Resource>();}

    else if (minfo.tname == "staywalk::Shader"){return std::make_shared<::staywalk::Shader>();}

    else if (minfo.tname == "staywalk::Tex2d"){return std::make_shared<::staywalk::Tex2d>();}

    else if (minfo.tname == "staywalk::RObject"){return std::make_shared<::staywalk::RObject>();}

    else if (minfo.tname == "staywalk::RTex"){return std::make_shared<::staywalk::RTex>();}

    else if (minfo.tname == "staywalk::RShader"){return std::make_shared<::staywalk::RShader>();}

    else if (minfo.tname == "staywalk::RProgram"){return std::make_shared<::staywalk::RProgram>();}

    else if (minfo.tname == "staywalk::RUniform"){return std::make_shared<::staywalk::RUniform>();}

    else if (minfo.tname == "staywalk::Material"){return std::make_shared<::staywalk::Material>();}

    else if (minfo.tname == "staywalk::RMesh"){return std::make_shared<::staywalk::RMesh>();}

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
