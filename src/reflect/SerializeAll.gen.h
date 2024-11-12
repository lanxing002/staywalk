namespace staywalk{
template<>
void staywalk::reflect::Serializer<GameObject>::dump(const GameObject& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.location, ofs);
    dumper.write(obj.scale, ofs);
    dumper.write(obj.rotation, ofs);
}


template<>
void staywalk::reflect::Serializer<GameObject>::load(GameObject& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
    loader.read(obj.location, ifs);
    loader.read(obj.scale, ifs);
    loader.read(obj.rotation, ifs);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<GameComponent>::dump(const GameComponent& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
}


template<>
void staywalk::reflect::Serializer<GameComponent>::load(GameComponent& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<RObject>::dump(const RObject& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.glid, ofs);
    dumper.write(obj.valid, ofs);
    dumper.write(obj.path, ofs);
}


template<>
void staywalk::reflect::Serializer<RObject>::load(RObject& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
    loader.read(obj.glid, ifs);
    loader.read(obj.valid, ifs);
    loader.read(obj.path, ifs);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<RTex>::dump(const RTex& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<RObject>::dump(obj, ofs, dumper);
}


template<>
void staywalk::reflect::Serializer<RTex>::load(RTex& obj, ifstream& ifs, Loader& loader) {
    Serializer<RObject>::load(obj, ifs, loader);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<RMesh>::dump(const RMesh& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<RObject>::dump(obj, ofs, dumper);
    dumper.write(obj.vertices_, ofs);
    dumper.write(obj.indices_, ofs);
    dumper.write(obj.mat_, ofs);
}


template<>
void staywalk::reflect::Serializer<RMesh>::load(RMesh& obj, ifstream& ifs, Loader& loader) {
    Serializer<RObject>::load(obj, ifs, loader);
    loader.read(obj.vertices_, ifs);
    loader.read(obj.indices_, ifs);
    loader.read(obj.mat_, ifs);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<Resource>::dump(const Resource& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.source, ofs);
    dumper.write(obj.dump_dir, ofs);
}


template<>
void staywalk::reflect::Serializer<Resource>::load(Resource& obj, ifstream& ifs, Loader& loader) {
    Serializer<Object>::load(obj, ifs, loader);
    loader.read(obj.source, ifs);
    loader.read(obj.dump_dir, ifs);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<Shader>::dump(const Shader& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Resource>::dump(obj, ofs, dumper);
    dumper.write(obj.code, ofs);
    dumper.write(obj.shader_type, ofs);
}


template<>
void staywalk::reflect::Serializer<Shader>::load(Shader& obj, ifstream& ifs, Loader& loader) {
    Serializer<Resource>::load(obj, ifs, loader);
    loader.read(obj.code, ifs);
    loader.read(obj.shader_type, ifs);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<StaticMeshComponent>::dump(const StaticMeshComponent& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<GameComponent>::dump(obj, ofs, dumper);
    dumper.write(obj.meshs, ofs);
}


template<>
void staywalk::reflect::Serializer<StaticMeshComponent>::load(StaticMeshComponent& obj, ifstream& ifs, Loader& loader) {
    Serializer<GameComponent>::load(obj, ifs, loader);
    loader.read(obj.meshs, ifs);
}
}


namespace staywalk{
template<>
void staywalk::reflect::Serializer<Actor>::dump(const Actor& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<GameObject>::dump(obj, ofs, dumper);
    dumper.write(obj.sm_comp, ofs);
}


template<>
void staywalk::reflect::Serializer<Actor>::load(Actor& obj, ifstream& ifs, Loader& loader) {
    Serializer<GameObject>::load(obj, ifs, loader);
    loader.read(obj.sm_comp, ifs);
}
}


