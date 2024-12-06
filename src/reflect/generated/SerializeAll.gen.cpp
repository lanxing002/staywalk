#include "Serialize.h"
#include "Object.h"

void ::staywalk::Object::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    {
        json::Value prop;
        dumper.write(this->name_, prop);
        value.AddMember("name_", prop, dumper.get_doc().GetAllocator()); 
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

    itr = value.FindMember("name_");
    if(itr != value.MemberEnd()){
        loader.read(this->name_, itr->value);
    }
    itr = value.FindMember("guid_");
    if(itr != value.MemberEnd()){
        loader.read(this->guid_, itr->value);
    }
}


bool ::staywalk::Object::operator==(const ::staywalk::Object& rhs) const {
    return 
true && ::staywalk::Comparer::equal(this->name_, rhs.name_) && ::staywalk::Comparer::equal(this->guid_, rhs.guid_);
}


::staywalk::reflect::MetaInfo staywalk::Object::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Object, "staywalk::Object"};

}

#include "GameObject.h"

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
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::GameObject, "staywalk::GameObject"};

}

#include "Actor.h"

void ::staywalk::Actor::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->sm_comp, prop);
        value.AddMember("sm_comp", prop, dumper.get_doc().GetAllocator()); 
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
}


bool ::staywalk::Actor::operator==(const ::staywalk::Actor& rhs) const {
    return 
GameObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->sm_comp, rhs.sm_comp);
}


::staywalk::reflect::MetaInfo staywalk::Actor::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Actor, "staywalk::Actor"};

}

#include "RenderObject.h"

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
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Resource, "staywalk::Resource"};

}

#include "RenderObject.h"

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
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Tex2d, "staywalk::Tex2d"};

}

#include "RenderObject.h"

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
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::RObject, "staywalk::RObject"};

}

#include "RenderObject.h"

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
    this->dump_post();
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
    this->load_post();
}


bool ::staywalk::RTex::operator==(const ::staywalk::RTex& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->tex, rhs.tex) && ::staywalk::Comparer::equal(this->mipmap, rhs.mipmap) && ::staywalk::Comparer::equal(this->wrap_s, rhs.wrap_s) && ::staywalk::Comparer::equal(this->wrap_t, rhs.wrap_t) && ::staywalk::Comparer::equal(this->min_filter, rhs.min_filter) && ::staywalk::Comparer::equal(this->mag_filter, rhs.mag_filter);
}


::staywalk::reflect::MetaInfo staywalk::RTex::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::RTex, "staywalk::RTex"};

}

#include "RProgram.h"

void ::staywalk::RShader::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->shadertype, prop);
        value.AddMember("shadertype", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->code, prop);
        value.AddMember("code", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::RShader::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("shadertype");
    if(itr != value.MemberEnd()){
        loader.read(this->shadertype, itr->value);
    }
    itr = value.FindMember("code");
    if(itr != value.MemberEnd()){
        loader.read(this->code, itr->value);
    }
}


bool ::staywalk::RShader::operator==(const ::staywalk::RShader& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->shadertype, rhs.shadertype) && ::staywalk::Comparer::equal(this->code, rhs.code);
}


::staywalk::reflect::MetaInfo staywalk::RShader::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::RShader, "staywalk::RShader"};

}

#include "RProgram.h"

void ::staywalk::RUniform::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->utype_, prop);
        value.AddMember("utype_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->data_, prop);
        value.AddMember("data_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::RUniform::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("utype_");
    if(itr != value.MemberEnd()){
        loader.read(this->utype_, itr->value);
    }
    itr = value.FindMember("data_");
    if(itr != value.MemberEnd()){
        loader.read(this->data_, itr->value);
    }
}


bool ::staywalk::RUniform::operator==(const ::staywalk::RUniform& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->utype_, rhs.utype_) && ::staywalk::Comparer::equal(this->data_, rhs.data_);
}


::staywalk::reflect::MetaInfo staywalk::RUniform::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::RUniform, "staywalk::RUniform"};

}

#include "RProgram.h"

void ::staywalk::RProgram::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->vs, prop);
        value.AddMember("vs", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->fs, prop);
        value.AddMember("fs", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->gs, prop);
        value.AddMember("gs", prop, dumper.get_doc().GetAllocator()); 
    }
    this->dump_post();
}


void ::staywalk::RProgram::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("vs");
    if(itr != value.MemberEnd()){
        loader.read(this->vs, itr->value);
    }
    itr = value.FindMember("fs");
    if(itr != value.MemberEnd()){
        loader.read(this->fs, itr->value);
    }
    itr = value.FindMember("gs");
    if(itr != value.MemberEnd()){
        loader.read(this->gs, itr->value);
    }
    this->load_post();
}


bool ::staywalk::RProgram::operator==(const ::staywalk::RProgram& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->vs, rhs.vs) && ::staywalk::Comparer::equal(this->fs, rhs.fs) && ::staywalk::Comparer::equal(this->gs, rhs.gs);
}


::staywalk::reflect::MetaInfo staywalk::RProgram::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::RProgram, "staywalk::RProgram"};

}

#include "Material.h"

void ::staywalk::Material::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->program, prop);
        value.AddMember("program", prop, dumper.get_doc().GetAllocator()); 
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
    {
        json::Value prop;
        dumper.write(this->vecce, prop);
        value.AddMember("vecce", prop, dumper.get_doc().GetAllocator()); 
    }
    this->dump_post();
}


void ::staywalk::Material::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("program");
    if(itr != value.MemberEnd()){
        loader.read(this->program, itr->value);
    }
    itr = value.FindMember("uniforms_");
    if(itr != value.MemberEnd()){
        loader.read(this->uniforms_, itr->value);
    }
    itr = value.FindMember("texs_");
    if(itr != value.MemberEnd()){
        loader.read(this->texs_, itr->value);
    }
    itr = value.FindMember("vecce");
    if(itr != value.MemberEnd()){
        loader.read(this->vecce, itr->value);
    }
    this->load_post();
}


bool ::staywalk::Material::operator==(const ::staywalk::Material& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->program, rhs.program) && ::staywalk::Comparer::equal(this->uniforms_, rhs.uniforms_) && ::staywalk::Comparer::equal(this->texs_, rhs.texs_) && ::staywalk::Comparer::equal(this->vecce, rhs.vecce);
}


::staywalk::reflect::MetaInfo staywalk::Material::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Material, "staywalk::Material"};

}

#include "Camera.h"

void ::staywalk::Camera::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->porject_type, prop);
        value.AddMember("porject_type", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->fov, prop);
        value.AddMember("fov", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->aspect, prop);
        value.AddMember("aspect", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->near, prop);
        value.AddMember("near", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->far, prop);
        value.AddMember("far", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Camera::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    GameObject::load(value, loader);

    itr = value.FindMember("porject_type");
    if(itr != value.MemberEnd()){
        loader.read(this->porject_type, itr->value);
    }
    itr = value.FindMember("fov");
    if(itr != value.MemberEnd()){
        loader.read(this->fov, itr->value);
    }
    itr = value.FindMember("aspect");
    if(itr != value.MemberEnd()){
        loader.read(this->aspect, itr->value);
    }
    itr = value.FindMember("near");
    if(itr != value.MemberEnd()){
        loader.read(this->near, itr->value);
    }
    itr = value.FindMember("far");
    if(itr != value.MemberEnd()){
        loader.read(this->far, itr->value);
    }
}


bool ::staywalk::Camera::operator==(const ::staywalk::Camera& rhs) const {
    return 
GameObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->porject_type, rhs.porject_type) && ::staywalk::Comparer::equal(this->fov, rhs.fov) && ::staywalk::Comparer::equal(this->aspect, rhs.aspect) && ::staywalk::Comparer::equal(this->near, rhs.near) && ::staywalk::Comparer::equal(this->far, rhs.far);
}


::staywalk::reflect::MetaInfo staywalk::Camera::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Camera, "staywalk::Camera"};

}

#include "Light.h"

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
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Light, "staywalk::Light"};

}

#include "GameComponent.h"

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
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::GameComponent, "staywalk::GameComponent"};

}

#include "RMesh.h"

void ::staywalk::Mesh::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    this->dump_post();
}


void ::staywalk::Mesh::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    this->load_post();
}


bool ::staywalk::Mesh::operator==(const ::staywalk::Mesh& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Mesh::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Mesh, "staywalk::Mesh"};

}

#include "StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    GameComponent::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->meshs, prop);
        value.AddMember("meshs", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->transform, prop);
        value.AddMember("transform", prop, dumper.get_doc().GetAllocator()); 
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
    itr = value.FindMember("transform");
    if(itr != value.MemberEnd()){
        loader.read(this->transform, itr->value);
    }
}


bool ::staywalk::StaticMeshComponent::operator==(const ::staywalk::StaticMeshComponent& rhs) const {
    return 
GameComponent::operator==(rhs)  && ::staywalk::Comparer::equal(this->meshs, rhs.meshs) && ::staywalk::Comparer::equal(this->transform, rhs.transform);
}


::staywalk::reflect::MetaInfo staywalk::StaticMeshComponent::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::StaticMeshComponent, "staywalk::StaticMeshComponent"};

}

#include "Terrain.h"

void ::staywalk::Terrain::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Actor::dump(value, dumper);

}


void ::staywalk::Terrain::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Actor::load(value, loader);

}


bool ::staywalk::Terrain::operator==(const ::staywalk::Terrain& rhs) const {
    return 
Actor::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Terrain::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Terrain, "staywalk::Terrain"};

}

