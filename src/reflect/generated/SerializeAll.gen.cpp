#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src\reflect\Serialize.h"
#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Object.h"

void ::staywalk::Object::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    {
        json::Value prop;
        dumper.write(this->name, prop);
        value.AddMember("name", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->guid_, prop);
        value.AddMember("guid_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Object::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    itr = value.FindMember("name");
    if(itr != value.MemberEnd()){
        loader.read(this->name, itr->value);
    }
    itr = value.FindMember("guid_");
    if(itr != value.MemberEnd()){
        loader.read(this->guid_, itr->value);
    }
}


bool ::staywalk::Object::operator==(const ::staywalk::Object& rhs) const {
    return 
true && ::staywalk::Comparer::equal(this->name, rhs.name) && ::staywalk::Comparer::equal(this->guid_, rhs.guid_);
}


::staywalk::reflect::MetaInfo staywalk::Object::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Object"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\GameObject.h"

void ::staywalk::GameObject::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->transform, prop);
        value.AddMember("transform", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::GameObject::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("transform");
    if(itr != value.MemberEnd()){
        loader.read(this->transform, itr->value);
    }
}


bool ::staywalk::GameObject::operator==(const ::staywalk::GameObject& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->transform, rhs.transform);
}


::staywalk::reflect::MetaInfo staywalk::GameObject::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::GameObject"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\GameComponent.h"

void ::staywalk::GameComponent::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

}


void ::staywalk::GameComponent::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

}


bool ::staywalk::GameComponent::operator==(const ::staywalk::GameComponent& rhs) const {
    return 
Object::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::GameComponent::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::GameComponent"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::Resource::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->source, prop);
        value.AddMember("source", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->dump_dir, prop);
        value.AddMember("dump_dir", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Resource::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("source");
    if(itr != value.MemberEnd()){
        loader.read(this->source, itr->value);
    }
    itr = value.FindMember("dump_dir");
    if(itr != value.MemberEnd()){
        loader.read(this->dump_dir, itr->value);
    }
}


bool ::staywalk::Resource::operator==(const ::staywalk::Resource& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->source, rhs.source) && ::staywalk::Comparer::equal(this->dump_dir, rhs.dump_dir);
}


::staywalk::reflect::MetaInfo staywalk::Resource::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Resource"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::Shader::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Resource::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->code, prop);
        value.AddMember("code", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->shader_type, prop);
        value.AddMember("shader_type", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Shader::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Resource::load(value, loader);

    itr = value.FindMember("code");
    if(itr != value.MemberEnd()){
        loader.read(this->code, itr->value);
    }
    itr = value.FindMember("shader_type");
    if(itr != value.MemberEnd()){
        loader.read(this->shader_type, itr->value);
    }
}


bool ::staywalk::Shader::operator==(const ::staywalk::Shader& rhs) const {
    return 
Resource::operator==(rhs)  && ::staywalk::Comparer::equal(this->code, rhs.code) && ::staywalk::Comparer::equal(this->shader_type, rhs.shader_type);
}


::staywalk::reflect::MetaInfo staywalk::Shader::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Shader"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::Tex2d::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Resource::dump(value, dumper);

}


void ::staywalk::Tex2d::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Resource::load(value, loader);

}


bool ::staywalk::Tex2d::operator==(const ::staywalk::Tex2d& rhs) const {
    return 
Resource::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Tex2d::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Tex2d"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::RObject::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

}


void ::staywalk::RObject::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

}


bool ::staywalk::RObject::operator==(const ::staywalk::RObject& rhs) const {
    return 
Object::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RObject::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RObject"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::RTex::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->tex, prop);
        value.AddMember("tex", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->mipmap, prop);
        value.AddMember("mipmap", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_s, prop);
        value.AddMember("wrap_s", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_t, prop);
        value.AddMember("wrap_t", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->min_filter, prop);
        value.AddMember("min_filter", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->mag_filter, prop);
        value.AddMember("mag_filter", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::RTex::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("tex");
    if(itr != value.MemberEnd()){
        loader.read(this->tex, itr->value);
    }
    itr = value.FindMember("mipmap");
    if(itr != value.MemberEnd()){
        loader.read(this->mipmap, itr->value);
    }
    itr = value.FindMember("wrap_s");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_s, itr->value);
    }
    itr = value.FindMember("wrap_t");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_t, itr->value);
    }
    itr = value.FindMember("min_filter");
    if(itr != value.MemberEnd()){
        loader.read(this->min_filter, itr->value);
    }
    itr = value.FindMember("mag_filter");
    if(itr != value.MemberEnd()){
        loader.read(this->mag_filter, itr->value);
    }
}


bool ::staywalk::RTex::operator==(const ::staywalk::RTex& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->tex, rhs.tex) && ::staywalk::Comparer::equal(this->mipmap, rhs.mipmap) && ::staywalk::Comparer::equal(this->wrap_s, rhs.wrap_s) && ::staywalk::Comparer::equal(this->wrap_t, rhs.wrap_t) && ::staywalk::Comparer::equal(this->min_filter, rhs.min_filter) && ::staywalk::Comparer::equal(this->mag_filter, rhs.mag_filter);
}


::staywalk::reflect::MetaInfo staywalk::RTex::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RTex"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::RShader::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

}


void ::staywalk::RShader::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

}


bool ::staywalk::RShader::operator==(const ::staywalk::RShader& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RShader::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RShader"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::RProgram::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

}


void ::staywalk::RProgram::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

}


bool ::staywalk::RProgram::operator==(const ::staywalk::RProgram& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RProgram::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RProgram"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RenderObject.h"

void ::staywalk::RUniform::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

}


void ::staywalk::RUniform::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

}


bool ::staywalk::RUniform::operator==(const ::staywalk::RUniform& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RUniform::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RUniform"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Material.h"

void ::staywalk::Material::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->shader_, prop);
        value.AddMember("shader_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->uniforms_, prop);
        value.AddMember("uniforms_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->texs_, prop);
        value.AddMember("texs_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Material::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("shader_");
    if(itr != value.MemberEnd()){
        loader.read(this->shader_, itr->value);
    }
    itr = value.FindMember("uniforms_");
    if(itr != value.MemberEnd()){
        loader.read(this->uniforms_, itr->value);
    }
    itr = value.FindMember("texs_");
    if(itr != value.MemberEnd()){
        loader.read(this->texs_, itr->value);
    }
}


bool ::staywalk::Material::operator==(const ::staywalk::Material& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->shader_, rhs.shader_) && ::staywalk::Comparer::equal(this->uniforms_, rhs.uniforms_) && ::staywalk::Comparer::equal(this->texs_, rhs.texs_);
}


::staywalk::reflect::MetaInfo staywalk::Material::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Material"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\RMesh.h"

void ::staywalk::RMesh::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->vertices, prop);
        value.AddMember("vertices", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->indices, prop);
        value.AddMember("indices", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->mat, prop);
        value.AddMember("mat", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::RMesh::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("vertices");
    if(itr != value.MemberEnd()){
        loader.read(this->vertices, itr->value);
    }
    itr = value.FindMember("indices");
    if(itr != value.MemberEnd()){
        loader.read(this->indices, itr->value);
    }
    itr = value.FindMember("mat");
    if(itr != value.MemberEnd()){
        loader.read(this->mat, itr->value);
    }
}


bool ::staywalk::RMesh::operator==(const ::staywalk::RMesh& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->vertices, rhs.vertices) && ::staywalk::Comparer::equal(this->indices, rhs.indices) && ::staywalk::Comparer::equal(this->mat, rhs.mat);
}


::staywalk::reflect::MetaInfo staywalk::RMesh::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RMesh"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameComponent::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->meshs, prop);
        value.AddMember("meshs", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::StaticMeshComponent::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    GameComponent::load(value, loader);

    itr = value.FindMember("meshs");
    if(itr != value.MemberEnd()){
        loader.read(this->meshs, itr->value);
    }
}


bool ::staywalk::StaticMeshComponent::operator==(const ::staywalk::StaticMeshComponent& rhs) const {
    return 
GameComponent::operator==(rhs)  && ::staywalk::Comparer::equal(this->meshs, rhs.meshs);
}


::staywalk::reflect::MetaInfo staywalk::StaticMeshComponent::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::StaticMeshComponent"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Actor.h"

void ::staywalk::Actor::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->sm_comp, prop);
        value.AddMember("sm_comp", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->ssm_comp, prop);
        value.AddMember("ssm_comp", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->shader_type, prop);
        value.AddMember("shader_type", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Actor::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    GameObject::load(value, loader);

    itr = value.FindMember("sm_comp");
    if(itr != value.MemberEnd()){
        loader.read(this->sm_comp, itr->value);
    }
    itr = value.FindMember("ssm_comp");
    if(itr != value.MemberEnd()){
        loader.read(this->ssm_comp, itr->value);
    }
    itr = value.FindMember("shader_type");
    if(itr != value.MemberEnd()){
        loader.read(this->shader_type, itr->value);
    }
}


bool ::staywalk::Actor::operator==(const ::staywalk::Actor& rhs) const {
    return 
GameObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->sm_comp, rhs.sm_comp) && ::staywalk::Comparer::equal(this->ssm_comp, rhs.ssm_comp) && ::staywalk::Comparer::equal(this->shader_type, rhs.shader_type);
}


::staywalk::reflect::MetaInfo staywalk::Actor::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Actor"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Camera.h"

void ::staywalk::Camera::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameObject::dump(value, dumper);

}


void ::staywalk::Camera::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    GameObject::load(value, loader);

}


bool ::staywalk::Camera::operator==(const ::staywalk::Camera& rhs) const {
    return 
GameObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Camera::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Camera"};

}

#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src/engine\Light.h"

void ::staywalk::Light::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameObject::dump(value, dumper);

}


void ::staywalk::Light::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    GameObject::load(value, loader);

}


bool ::staywalk::Light::operator==(const ::staywalk::Light& rhs) const {
    return 
GameObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Light::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Light"};

}

