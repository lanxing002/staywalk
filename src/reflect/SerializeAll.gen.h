#include "Common.gen.h"

void Serializer<staywalk::GameObject>::dump(const staywalk::GameObject& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.location, ofs);
    dumper.write(obj.scale, ofs);
    dumper.write(obj.rotation, ofs);
}


void Serializer<staywalk::GameComponent>::dump(const staywalk::GameComponent& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
}


void Serializer<staywalk::RObject>::dump(const staywalk::RObject& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.glid, ofs);
    dumper.write(obj.valid, ofs);
    dumper.write(obj.path, ofs);
}


void Serializer<staywalk::RTex>::dump(const staywalk::RTex& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<RObject>::dump(obj, ofs, dumper);
}


void Serializer<staywalk::RMesh>::dump(const staywalk::RMesh& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<RObject>::dump(obj, ofs, dumper);
    dumper.write(obj.vertices_, ofs);
    dumper.write(obj.indices_, ofs);
    dumper.write(obj.mat_, ofs);
}


void Serializer<staywalk::Resource>::dump(const staywalk::Resource& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Object>::dump(obj, ofs, dumper);
    dumper.write(obj.source, ofs);
    dumper.write(obj.dump_dir, ofs);
}


void Serializer<staywalk::Shader>::dump(const staywalk::Shader& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<Resource>::dump(obj, ofs, dumper);
    dumper.write(obj.code, ofs);
    dumper.write(obj.shader_type, ofs);
}


void Serializer<staywalk::StaticMeshComponent>::dump(const staywalk::StaticMeshComponent& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<GameComponent>::dump(obj, ofs, dumper);
    dumper.write(obj.meshs, ofs);
}


void Serializer<staywalk::Actor>::dump(const staywalk::Actor& obj, ofstream& ofs, Dumper& dumper) {
    Serializer<GameObject>::dump(obj, ofs, dumper);
    dumper.write(obj.sm_comp, ofs);
}

