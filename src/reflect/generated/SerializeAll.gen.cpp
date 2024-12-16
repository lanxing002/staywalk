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

#include "Entity.h"

void ::staywalk::Entity::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->transform_, prop);
        value.AddMember("transform_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Entity::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("transform_");
    if(itr != value.MemberEnd()){
        loader.read(this->transform_, itr->value);
    }
}


bool ::staywalk::Entity::operator==(const ::staywalk::Entity& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->transform_, rhs.transform_);
}


::staywalk::reflect::MetaInfo staywalk::Entity::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Entity, "staywalk::Entity"};

}

#include "Actor.h"

void ::staywalk::Actor::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Entity::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->sm_comp_, prop);
        value.AddMember("sm_comp_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->skeleton_comp_, prop);
        value.AddMember("skeleton_comp_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Actor::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Entity::load(value, loader);

    itr = value.FindMember("sm_comp_");
    if(itr != value.MemberEnd()){
        loader.read(this->sm_comp_, itr->value);
    }
    itr = value.FindMember("skeleton_comp_");
    if(itr != value.MemberEnd()){
        loader.read(this->skeleton_comp_, itr->value);
    }
}


bool ::staywalk::Actor::operator==(const ::staywalk::Actor& rhs) const {
    return 
Entity::operator==(rhs)  && ::staywalk::Comparer::equal(this->sm_comp_, rhs.sm_comp_) && ::staywalk::Comparer::equal(this->skeleton_comp_, rhs.skeleton_comp_);
}


::staywalk::reflect::MetaInfo staywalk::Actor::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Actor, "staywalk::Actor"};

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

void ::staywalk::Tex2D::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->mipmap_, prop);
        value.AddMember("mipmap_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_s_, prop);
        value.AddMember("wrap_s_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_t_, prop);
        value.AddMember("wrap_t_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->min_filter_, prop);
        value.AddMember("min_filter_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->mag_filter_, prop);
        value.AddMember("mag_filter_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->img_name_, prop);
        value.AddMember("img_name_", prop, dumper.get_doc().GetAllocator()); 
    }
    this->dump_post();
}


void ::staywalk::Tex2D::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("mipmap_");
    if(itr != value.MemberEnd()){
        loader.read(this->mipmap_, itr->value);
    }
    itr = value.FindMember("wrap_s_");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_s_, itr->value);
    }
    itr = value.FindMember("wrap_t_");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_t_, itr->value);
    }
    itr = value.FindMember("min_filter_");
    if(itr != value.MemberEnd()){
        loader.read(this->min_filter_, itr->value);
    }
    itr = value.FindMember("mag_filter_");
    if(itr != value.MemberEnd()){
        loader.read(this->mag_filter_, itr->value);
    }
    itr = value.FindMember("img_name_");
    if(itr != value.MemberEnd()){
        loader.read(this->img_name_, itr->value);
    }
    this->load_post();
}


bool ::staywalk::Tex2D::operator==(const ::staywalk::Tex2D& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->mipmap_, rhs.mipmap_) && ::staywalk::Comparer::equal(this->wrap_s_, rhs.wrap_s_) && ::staywalk::Comparer::equal(this->wrap_t_, rhs.wrap_t_) && ::staywalk::Comparer::equal(this->min_filter_, rhs.min_filter_) && ::staywalk::Comparer::equal(this->mag_filter_, rhs.mag_filter_) && ::staywalk::Comparer::equal(this->img_name_, rhs.img_name_);
}


::staywalk::reflect::MetaInfo staywalk::Tex2D::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Tex2D, "staywalk::Tex2D"};

}

#include "RenderObject.h"

void ::staywalk::CubeMap::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->img_name_, prop);
        value.AddMember("img_name_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->img_extension_, prop);
        value.AddMember("img_extension_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_s_, prop);
        value.AddMember("wrap_s_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_t_, prop);
        value.AddMember("wrap_t_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->wrap_r_, prop);
        value.AddMember("wrap_r_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->min_filter_, prop);
        value.AddMember("min_filter_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->mag_filter_, prop);
        value.AddMember("mag_filter_", prop, dumper.get_doc().GetAllocator()); 
    }
    this->dump_post();
}


void ::staywalk::CubeMap::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("img_name_");
    if(itr != value.MemberEnd()){
        loader.read(this->img_name_, itr->value);
    }
    itr = value.FindMember("img_extension_");
    if(itr != value.MemberEnd()){
        loader.read(this->img_extension_, itr->value);
    }
    itr = value.FindMember("wrap_s_");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_s_, itr->value);
    }
    itr = value.FindMember("wrap_t_");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_t_, itr->value);
    }
    itr = value.FindMember("wrap_r_");
    if(itr != value.MemberEnd()){
        loader.read(this->wrap_r_, itr->value);
    }
    itr = value.FindMember("min_filter_");
    if(itr != value.MemberEnd()){
        loader.read(this->min_filter_, itr->value);
    }
    itr = value.FindMember("mag_filter_");
    if(itr != value.MemberEnd()){
        loader.read(this->mag_filter_, itr->value);
    }
    this->load_post();
}


bool ::staywalk::CubeMap::operator==(const ::staywalk::CubeMap& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->img_name_, rhs.img_name_) && ::staywalk::Comparer::equal(this->img_extension_, rhs.img_extension_) && ::staywalk::Comparer::equal(this->wrap_s_, rhs.wrap_s_) && ::staywalk::Comparer::equal(this->wrap_t_, rhs.wrap_t_) && ::staywalk::Comparer::equal(this->wrap_r_, rhs.wrap_r_) && ::staywalk::Comparer::equal(this->min_filter_, rhs.min_filter_) && ::staywalk::Comparer::equal(this->mag_filter_, rhs.mag_filter_);
}


::staywalk::reflect::MetaInfo staywalk::CubeMap::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::CubeMap, "staywalk::CubeMap"};

}

#include "RProgram.h"

void ::staywalk::Shader::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->shadertype_, prop);
        value.AddMember("shadertype_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->code_, prop);
        value.AddMember("code_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Shader::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("shadertype_");
    if(itr != value.MemberEnd()){
        loader.read(this->shadertype_, itr->value);
    }
    itr = value.FindMember("code_");
    if(itr != value.MemberEnd()){
        loader.read(this->code_, itr->value);
    }
}


bool ::staywalk::Shader::operator==(const ::staywalk::Shader& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->shadertype_, rhs.shadertype_) && ::staywalk::Comparer::equal(this->code_, rhs.code_);
}


::staywalk::reflect::MetaInfo staywalk::Shader::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Shader, "staywalk::Shader"};

}

#include "RProgram.h"

void ::staywalk::Uniform::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
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


void ::staywalk::Uniform::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
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


bool ::staywalk::Uniform::operator==(const ::staywalk::Uniform& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->utype_, rhs.utype_) && ::staywalk::Comparer::equal(this->data_, rhs.data_);
}


::staywalk::reflect::MetaInfo staywalk::Uniform::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Uniform, "staywalk::Uniform"};

}

#include "RProgram.h"

void ::staywalk::Program::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->vs_, prop);
        value.AddMember("vs_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->fs_, prop);
        value.AddMember("fs_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->gs_, prop);
        value.AddMember("gs_", prop, dumper.get_doc().GetAllocator()); 
    }
    this->dump_post();
}


void ::staywalk::Program::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("vs_");
    if(itr != value.MemberEnd()){
        loader.read(this->vs_, itr->value);
    }
    itr = value.FindMember("fs_");
    if(itr != value.MemberEnd()){
        loader.read(this->fs_, itr->value);
    }
    itr = value.FindMember("gs_");
    if(itr != value.MemberEnd()){
        loader.read(this->gs_, itr->value);
    }
    this->load_post();
}


bool ::staywalk::Program::operator==(const ::staywalk::Program& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->vs_, rhs.vs_) && ::staywalk::Comparer::equal(this->fs_, rhs.fs_) && ::staywalk::Comparer::equal(this->gs_, rhs.gs_);
}


::staywalk::reflect::MetaInfo staywalk::Program::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Program, "staywalk::Program"};

}

#include "Material.h"

void ::staywalk::Material::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->program_, prop);
        value.AddMember("program_", prop, dumper.get_doc().GetAllocator()); 
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
    this->dump_post();
}


void ::staywalk::Material::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("program_");
    if(itr != value.MemberEnd()){
        loader.read(this->program_, itr->value);
    }
    itr = value.FindMember("uniforms_");
    if(itr != value.MemberEnd()){
        loader.read(this->uniforms_, itr->value);
    }
    itr = value.FindMember("texs_");
    if(itr != value.MemberEnd()){
        loader.read(this->texs_, itr->value);
    }
    this->load_post();
}


bool ::staywalk::Material::operator==(const ::staywalk::Material& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->program_, rhs.program_) && ::staywalk::Comparer::equal(this->uniforms_, rhs.uniforms_) && ::staywalk::Comparer::equal(this->texs_, rhs.texs_);
}


::staywalk::reflect::MetaInfo staywalk::Material::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Material, "staywalk::Material"};

}

#include "Camera.h"

void ::staywalk::Camera::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Entity::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->porject_type_, prop);
        value.AddMember("porject_type_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->fov_, prop);
        value.AddMember("fov_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->aspect_, prop);
        value.AddMember("aspect_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->near_, prop);
        value.AddMember("near_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->far_, prop);
        value.AddMember("far_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::Camera::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Entity::load(value, loader);

    itr = value.FindMember("porject_type_");
    if(itr != value.MemberEnd()){
        loader.read(this->porject_type_, itr->value);
    }
    itr = value.FindMember("fov_");
    if(itr != value.MemberEnd()){
        loader.read(this->fov_, itr->value);
    }
    itr = value.FindMember("aspect_");
    if(itr != value.MemberEnd()){
        loader.read(this->aspect_, itr->value);
    }
    itr = value.FindMember("near_");
    if(itr != value.MemberEnd()){
        loader.read(this->near_, itr->value);
    }
    itr = value.FindMember("far_");
    if(itr != value.MemberEnd()){
        loader.read(this->far_, itr->value);
    }
}


bool ::staywalk::Camera::operator==(const ::staywalk::Camera& rhs) const {
    return 
Entity::operator==(rhs)  && ::staywalk::Comparer::equal(this->porject_type_, rhs.porject_type_) && ::staywalk::Comparer::equal(this->fov_, rhs.fov_) && ::staywalk::Comparer::equal(this->aspect_, rhs.aspect_) && ::staywalk::Comparer::equal(this->near_, rhs.near_) && ::staywalk::Comparer::equal(this->far_, rhs.far_);
}


::staywalk::reflect::MetaInfo staywalk::Camera::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Camera, "staywalk::Camera"};

}

#include "Light.h"

void ::staywalk::RLight::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Entity::dump(value, dumper);

}


void ::staywalk::RLight::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Entity::load(value, loader);

}


bool ::staywalk::RLight::operator==(const ::staywalk::RLight& rhs) const {
    return 
Entity::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RLight::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::RLight, "staywalk::RLight"};

}

#include "Component.h"

void ::staywalk::Component::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

}


void ::staywalk::Component::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

}


bool ::staywalk::Component::operator==(const ::staywalk::Component& rhs) const {
    return 
Object::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Component::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Component, "staywalk::Component"};

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

#include "RMesh.h"

void ::staywalk::SkeletonMesh::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    this->dump_post();
}


void ::staywalk::SkeletonMesh::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    this->load_post();
}


bool ::staywalk::SkeletonMesh::operator==(const ::staywalk::SkeletonMesh& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::SkeletonMesh::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::SkeletonMesh, "staywalk::SkeletonMesh"};

}

#include "StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Component::dump(value, dumper);

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

    Component::load(value, loader);

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
Component::operator==(rhs)  && ::staywalk::Comparer::equal(this->meshs, rhs.meshs) && ::staywalk::Comparer::equal(this->transform, rhs.transform);
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

#include "Animation.h"

void ::staywalk::BoneTreeNode::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Object::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->transform_, prop);
        value.AddMember("transform_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->children_, prop);
        value.AddMember("children_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->bone_id_, prop);
        value.AddMember("bone_id_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::BoneTreeNode::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Object::load(value, loader);

    itr = value.FindMember("transform_");
    if(itr != value.MemberEnd()){
        loader.read(this->transform_, itr->value);
    }
    itr = value.FindMember("children_");
    if(itr != value.MemberEnd()){
        loader.read(this->children_, itr->value);
    }
    itr = value.FindMember("bone_id_");
    if(itr != value.MemberEnd()){
        loader.read(this->bone_id_, itr->value);
    }
}


bool ::staywalk::BoneTreeNode::operator==(const ::staywalk::BoneTreeNode& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->transform_, rhs.transform_) && ::staywalk::Comparer::equal(this->children_, rhs.children_) && ::staywalk::Comparer::equal(this->bone_id_, rhs.bone_id_);
}


::staywalk::reflect::MetaInfo staywalk::BoneTreeNode::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::BoneTreeNode, "staywalk::BoneTreeNode"};

}

#include "Animation.h"

void ::staywalk::Animation::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    RObject::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->curr_time_, prop);
        value.AddMember("curr_time_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->duration_, prop);
        value.AddMember("duration_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->ticks_pers_, prop);
        value.AddMember("ticks_pers_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->node_root_, prop);
        value.AddMember("node_root_", prop, dumper.get_doc().GetAllocator()); 
    }
    this->dump_post();
}


void ::staywalk::Animation::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    RObject::load(value, loader);

    itr = value.FindMember("curr_time_");
    if(itr != value.MemberEnd()){
        loader.read(this->curr_time_, itr->value);
    }
    itr = value.FindMember("duration_");
    if(itr != value.MemberEnd()){
        loader.read(this->duration_, itr->value);
    }
    itr = value.FindMember("ticks_pers_");
    if(itr != value.MemberEnd()){
        loader.read(this->ticks_pers_, itr->value);
    }
    itr = value.FindMember("node_root_");
    if(itr != value.MemberEnd()){
        loader.read(this->node_root_, itr->value);
    }
    this->load_post();
}


bool ::staywalk::Animation::operator==(const ::staywalk::Animation& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->curr_time_, rhs.curr_time_) && ::staywalk::Comparer::equal(this->duration_, rhs.duration_) && ::staywalk::Comparer::equal(this->ticks_pers_, rhs.ticks_pers_) && ::staywalk::Comparer::equal(this->node_root_, rhs.node_root_);
}


::staywalk::reflect::MetaInfo staywalk::Animation::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::Animation, "staywalk::Animation"};

}

#include "SkeletonMeshComponent.h"

void ::staywalk::SkeletonMeshComponent::dump(rapidjson::Value& value, ::staywalk::reflect::Dumper& dumper) const {
    assert(value.IsObject());

    Component::dump(value, dumper);

    {
        json::Value prop;
        dumper.write(this->transform_, prop);
        value.AddMember("transform_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->meshs_, prop);
        value.AddMember("meshs_", prop, dumper.get_doc().GetAllocator()); 
    }
    {
        json::Value prop;
        dumper.write(this->animation_, prop);
        value.AddMember("animation_", prop, dumper.get_doc().GetAllocator()); 
    }
}


void ::staywalk::SkeletonMeshComponent::load(rapidjson::Value& value, ::staywalk::reflect::Loader& loader) {
    assert(value.IsObject());
    json::Value::MemberIterator itr;

    Component::load(value, loader);

    itr = value.FindMember("transform_");
    if(itr != value.MemberEnd()){
        loader.read(this->transform_, itr->value);
    }
    itr = value.FindMember("meshs_");
    if(itr != value.MemberEnd()){
        loader.read(this->meshs_, itr->value);
    }
    itr = value.FindMember("animation_");
    if(itr != value.MemberEnd()){
        loader.read(this->animation_, itr->value);
    }
}


bool ::staywalk::SkeletonMeshComponent::operator==(const ::staywalk::SkeletonMeshComponent& rhs) const {
    return 
Component::operator==(rhs)  && ::staywalk::Comparer::equal(this->transform_, rhs.transform_) && ::staywalk::Comparer::equal(this->meshs_, rhs.meshs_) && ::staywalk::Comparer::equal(this->animation_, rhs.animation_);
}


::staywalk::reflect::MetaInfo staywalk::SkeletonMeshComponent::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{::staywalk::reflect::ObjectType::SkeletonMeshComponent, "staywalk::SkeletonMeshComponent"};

}

