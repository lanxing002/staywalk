#include "C:\Users\Lenovo\Documents\gly\git_stars\gl\staywalk\src\reflect\Serialize.h"
template<>
void ::staywalk::reflect::Serializer<::staywalk::Object>::dump(const ::staywalk::Object& obj, ofstream& ofs, Dumper& dumper) {
    dumper.write(obj.name, ofs);
    dumper.write(obj.guid_, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Object>::load(::staywalk::Object& obj, ifstream& ifs, Loader& loader) {
    loader.read(obj.name, ifs);
    loader.read(obj.guid_, ifs);
}


bool ::staywalk::Object::operator==(const ::staywalk::Object& rhs){
    return 
true && ::staywalk::Comparer::equal(this->name, rhs.name) && ::staywalk::Comparer::equal(this->guid_, rhs.guid_);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::GameObject>::dump(const ::staywalk::GameObject& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.location, ofs);
    dumper.write(obj.scale, ofs);
    dumper.write(obj.rotation, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::GameObject>::load(::staywalk::GameObject& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
    loader.read(obj.location, ifs);
    loader.read(obj.scale, ifs);
    loader.read(obj.rotation, ifs);
}


bool ::staywalk::GameObject::operator==(const ::staywalk::GameObject& rhs){
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->location, rhs.location) && ::staywalk::Comparer::equal(this->scale, rhs.scale) && ::staywalk::Comparer::equal(this->rotation, rhs.rotation);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::GameComponent>::dump(const ::staywalk::GameComponent& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::GameComponent>::load(::staywalk::GameComponent& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
}


bool ::staywalk::GameComponent::operator==(const ::staywalk::GameComponent& rhs){
    return 
Object::operator==(rhs) ;
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::RObject>::dump(const ::staywalk::RObject& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.glid, ofs);
    dumper.write(obj.valid, ofs);
    dumper.write(obj.path, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::RObject>::load(::staywalk::RObject& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
    loader.read(obj.glid, ifs);
    loader.read(obj.valid, ifs);
    loader.read(obj.path, ifs);
}


bool ::staywalk::RObject::operator==(const ::staywalk::RObject& rhs){
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->glid, rhs.glid) && ::staywalk::Comparer::equal(this->valid, rhs.valid) && ::staywalk::Comparer::equal(this->path, rhs.path);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::RTex>::dump(const ::staywalk::RTex& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<RObject>::dump(obj, ofs, dumper);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::RTex>::load(::staywalk::RTex& obj, ifstream& ifs, Loader& loader) {
    Serializer<RObject>::load(obj, ifs, loader);
}


bool ::staywalk::RTex::operator==(const ::staywalk::RTex& rhs){
    return 
RObject::operator==(rhs) ;
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::RMesh>::dump(const ::staywalk::RMesh& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<RObject>::dump(obj, ofs, dumper);
    dumper.write(obj.vertices_, ofs);
    dumper.write(obj.indices_, ofs);
    dumper.write(obj.mat_, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::RMesh>::load(::staywalk::RMesh& obj, ifstream& ifs, Loader& loader) {
    Serializer<RObject>::load(obj, ifs, loader);
    loader.read(obj.vertices_, ifs);
    loader.read(obj.indices_, ifs);
    loader.read(obj.mat_, ifs);
}


bool ::staywalk::RMesh::operator==(const ::staywalk::RMesh& rhs){
    return 
RObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->vertices_, rhs.vertices_) && ::staywalk::Comparer::equal(this->indices_, rhs.indices_) && ::staywalk::Comparer::equal(this->mat_, rhs.mat_);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Resource>::dump(const ::staywalk::Resource& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.source, ofs);
    dumper.write(obj.dump_dir, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Resource>::load(::staywalk::Resource& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
    loader.read(obj.source, ifs);
    loader.read(obj.dump_dir, ifs);
}


bool ::staywalk::Resource::operator==(const ::staywalk::Resource& rhs){
    return 
Object::operator==(rhs)  && ::staywalk::Comparer::equal(this->source, rhs.source) && ::staywalk::Comparer::equal(this->dump_dir, rhs.dump_dir);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Shader>::dump(const ::staywalk::Shader& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Resource>::dump(obj, ofs, dumper);
    dumper.write(obj.code, ofs);
    dumper.write(obj.shader_type, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Shader>::load(::staywalk::Shader& obj, ifstream& ifs, Loader& loader) {
    Serializer<Resource>::load(obj, ifs, loader);
    loader.read(obj.code, ifs);
    loader.read(obj.shader_type, ifs);
}


bool ::staywalk::Shader::operator==(const ::staywalk::Shader& rhs){
    return 
Resource::operator==(rhs)  && ::staywalk::Comparer::equal(this->code, rhs.code) && ::staywalk::Comparer::equal(this->shader_type, rhs.shader_type);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::StaticMeshComponent>::dump(const ::staywalk::StaticMeshComponent& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<GameComponent>::dump(obj, ofs, dumper);
    dumper.write(obj.meshs, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::StaticMeshComponent>::load(::staywalk::StaticMeshComponent& obj, ifstream& ifs, Loader& loader) {
    Serializer<GameComponent>::load(obj, ifs, loader);
    loader.read(obj.meshs, ifs);
}


bool ::staywalk::StaticMeshComponent::operator==(const ::staywalk::StaticMeshComponent& rhs){
    return 
GameComponent::operator==(rhs)  && ::staywalk::Comparer::equal(this->meshs, rhs.meshs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Actor>::dump(const ::staywalk::Actor& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<GameObject>::dump(obj, ofs, dumper);
    dumper.write(obj.sm_comp, ofs);
}


template<>
void ::staywalk::reflect::Serializer<::staywalk::Actor>::load(::staywalk::Actor& obj, ifstream& ifs, Loader& loader) {
    Serializer<GameObject>::load(obj, ifs, loader);
    loader.read(obj.sm_comp, ifs);
}


bool ::staywalk::Actor::operator==(const ::staywalk::Actor& rhs){
    return 
GameObject::operator==(rhs)  && ::staywalk::Comparer::equal(this->sm_comp, rhs.sm_comp);
}

