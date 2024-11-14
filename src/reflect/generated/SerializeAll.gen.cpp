#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src\reflect\Serialize.h"
#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Object.h"

void ::staywalk::Object::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    dumper.write(this->name, ofs);
    dumper.write(this->guid_, ofs);
}


void ::staywalk::Object::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    loader.read(this->name, ifs);
    loader.read(this->guid_, ifs);
}


bool ::staywalk::Object::operator==(const ::staywalk::Object& rhs) const {
    return 
true && ::staywalk::Comparer::equal(this->name, rhs.name) && ::staywalk::Comparer::equal(this->guid_, rhs.guid_);
}


::staywalk::reflect::MetaInfo staywalk::Object::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Object"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\GameObject.h"

void ::staywalk::GameObject::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Object::dump(ofs, dumper);
    dumper.write(this->location, ofs);
    dumper.write(this->scale, ofs);
    dumper.write(this->rotation, ofs);
}


void ::staywalk::GameObject::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Object::load(ifs, loader);
    loader.read(this->location, ifs);
    loader.read(this->scale, ifs);
    loader.read(this->rotation, ifs);
}


bool ::staywalk::GameObject::operator==(const ::staywalk::GameObject& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->location, rhs.location) && ::staywalk::Comparer::equal(this->scale, rhs.scale) && ::staywalk::Comparer::equal(this->rotation, rhs.rotation);
}


::staywalk::reflect::MetaInfo staywalk::GameObject::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::GameObject"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\GameComponent.h"

void ::staywalk::GameComponent::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Object::dump(ofs, dumper);
}


void ::staywalk::GameComponent::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Object::load(ifs, loader);
}


bool ::staywalk::GameComponent::operator==(const ::staywalk::GameComponent& rhs) const {
    return 
Object::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::GameComponent::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::GameComponent"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RObject::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Object::dump(ofs, dumper);
    dumper.write(this->glid, ofs);
    dumper.write(this->valid, ofs);
    dumper.write(this->path, ofs);
}


void ::staywalk::RObject::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Object::load(ifs, loader);
    loader.read(this->glid, ifs);
    loader.read(this->valid, ifs);
    loader.read(this->path, ifs);
}


bool ::staywalk::RObject::operator==(const ::staywalk::RObject& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->glid, rhs.glid) && ::staywalk::Comparer::equal(this->valid, rhs.valid) && ::staywalk::Comparer::equal(this->path, rhs.path);
}


::staywalk::reflect::MetaInfo staywalk::RObject::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RObject"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RTex::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    RObject::dump(ofs, dumper);
}


void ::staywalk::RTex::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    RObject::load(ifs, loader);
}


bool ::staywalk::RTex::operator==(const ::staywalk::RTex& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RTex::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RTex"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RShader::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    RObject::dump(ofs, dumper);
}


void ::staywalk::RShader::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    RObject::load(ifs, loader);
}


bool ::staywalk::RShader::operator==(const ::staywalk::RShader& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RShader::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RShader"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RProgram::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    RObject::dump(ofs, dumper);
}


void ::staywalk::RProgram::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    RObject::load(ifs, loader);
}


bool ::staywalk::RProgram::operator==(const ::staywalk::RProgram& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RProgram::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RProgram"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::RUniform::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    RObject::dump(ofs, dumper);
}


void ::staywalk::RUniform::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    RObject::load(ifs, loader);
}


bool ::staywalk::RUniform::operator==(const ::staywalk::RUniform& rhs) const {
    return 
RObject::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::RUniform::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RUniform"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::Resource::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Object::dump(ofs, dumper);
    dumper.write(this->source, ofs);
    dumper.write(this->dump_dir, ofs);
}


void ::staywalk::Resource::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Object::load(ifs, loader);
    loader.read(this->source, ifs);
    loader.read(this->dump_dir, ifs);
}


bool ::staywalk::Resource::operator==(const ::staywalk::Resource& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->source, rhs.source) && ::staywalk::Comparer::equal(this->dump_dir, rhs.dump_dir);
}


::staywalk::reflect::MetaInfo staywalk::Resource::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Resource"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::Shader::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Resource::dump(ofs, dumper);
    dumper.write(this->code, ofs);
    dumper.write(this->shader_type, ofs);
}


void ::staywalk::Shader::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Resource::load(ifs, loader);
    loader.read(this->code, ifs);
    loader.read(this->shader_type, ifs);
}


bool ::staywalk::Shader::operator==(const ::staywalk::Shader& rhs) const {
    return 
Resource::operator==(rhs)  && ::staywalk::Comparer::equal(this->code, rhs.code) && ::staywalk::Comparer::equal(this->shader_type, rhs.shader_type);
}


::staywalk::reflect::MetaInfo staywalk::Shader::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Shader"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RenderObject.h"

void ::staywalk::Tex2d::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Resource::dump(ofs, dumper);
}


void ::staywalk::Tex2d::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Resource::load(ifs, loader);
}


bool ::staywalk::Tex2d::operator==(const ::staywalk::Tex2d& rhs) const {
    return 
Resource::operator==(rhs) ;
}


::staywalk::reflect::MetaInfo staywalk::Tex2d::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Tex2d"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Material.h"

void ::staywalk::Material::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    Object::dump(ofs, dumper);
    dumper.write(this->shader_, ofs);
    dumper.write(this->uniforms_, ofs);
    dumper.write(this->texs_, ofs);
}


void ::staywalk::Material::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    Object::load(ifs, loader);
    loader.read(this->shader_, ifs);
    loader.read(this->uniforms_, ifs);
    loader.read(this->texs_, ifs);
}


bool ::staywalk::Material::operator==(const ::staywalk::Material& rhs) const {
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->shader_, rhs.shader_) && ::staywalk::Comparer::equal(this->uniforms_, rhs.uniforms_) && ::staywalk::Comparer::equal(this->texs_, rhs.texs_);
}


::staywalk::reflect::MetaInfo staywalk::Material::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Material"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\RMesh.h"

void ::staywalk::RMesh::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    RObject::dump(ofs, dumper);
    dumper.write(this->vertices_, ofs);
    dumper.write(this->indices_, ofs);
    dumper.write(this->mat_, ofs);
}


void ::staywalk::RMesh::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    RObject::load(ifs, loader);
    loader.read(this->vertices_, ifs);
    loader.read(this->indices_, ifs);
    loader.read(this->mat_, ifs);
}


bool ::staywalk::RMesh::operator==(const ::staywalk::RMesh& rhs) const {
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->vertices_, rhs.vertices_) && ::staywalk::Comparer::equal(this->indices_, rhs.indices_) && ::staywalk::Comparer::equal(this->mat_, rhs.mat_);
}


::staywalk::reflect::MetaInfo staywalk::RMesh::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::RMesh"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\StaticMeshComponent.h"

void ::staywalk::StaticMeshComponent::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    GameComponent::dump(ofs, dumper);
    dumper.write(this->meshs, ofs);
}


void ::staywalk::StaticMeshComponent::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    GameComponent::load(ifs, loader);
    loader.read(this->meshs, ifs);
}


bool ::staywalk::StaticMeshComponent::operator==(const ::staywalk::StaticMeshComponent& rhs) const {
    return 
GameComponent::operator==(rhs)  && ::staywalk::Comparer::equal(this->meshs, rhs.meshs);
}


::staywalk::reflect::MetaInfo staywalk::StaticMeshComponent::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::StaticMeshComponent"};

}

#include "C:/Users/Lenovo/Documents/gly/git_stars/gl/staywalk/src/engine\Actor.h"

void ::staywalk::Actor::dump(::staywalk::ofstream& ofs, ::staywalk::reflect::Dumper& dumper) const {
    GameObject::dump(ofs, dumper);
    dumper.write(this->sm_comp, ofs);
}


void ::staywalk::Actor::load(::staywalk::ifstream& ifs, ::staywalk::reflect::Loader& loader) {
    GameObject::load(ifs, loader);
    loader.read(this->sm_comp, ifs);
}


bool ::staywalk::Actor::operator==(const ::staywalk::Actor& rhs) const {
    return 
GameObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->sm_comp, rhs.sm_comp);
}


::staywalk::reflect::MetaInfo staywalk::Actor::get_meta_info() const {
    return ::staywalk::reflect::MetaInfo{"staywalk::Actor"};

}

