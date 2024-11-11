#include "RenderObject.h"
#include "Utility.h"
#include "Material.h"
//
//namespace staywalk {
//	//RMesh RShader RProgram RUniform
//
//	RObject::RObject(const string& name)
//	:Object(name){
//	}
//
//	/****************** RObject ********************/
//	bool RObject::operator==(const RObject& rhs) {
//		if (!Object::operator==(rhs)) return false;
//		return true;
//	}
//
//	void RObject::dump_impl(ofstream& ofs, Dumper& dumper) const {
//		Object::dump_impl(ofs, dumper);
//
//	}
//
//	void RObject::load_impl(ifstream& ifs, Loader& loader) {
//		Object::load_impl(ifs, loader);
//	}
//
//	/****************** RTex ********************/
//	bool RTex::operator==(const RTex& rhs) {
//		if (!RObject::operator==(rhs)) return false;
//		return true;
//	}
//	
//	void RTex::dump_impl(ofstream& ofs, Dumper& dumper) const {
//		RObject::dump_impl(ofs, dumper);
//
//	}
//
//	void RTex::load_impl(ifstream& ifs, Loader& loader) {
//		RObject::load_impl(ifs, loader);
//	}
//
//
//	/****************** RMesh ********************/
//	RMesh::RMesh(const string& name)
//		:RObject(name) {
//
//	}
//
//	RMesh::RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name) 
//		:RObject(name), vertices_(vv), indices_(ii){
//
//	}
//
//	bool RMesh::operator==(const RMesh& rhs) {
//		if (!RObject::operator==(rhs)) return false;
//		if (!Utility::equal(vertices_, rhs.vertices_)) return false;
//		if (!Utility::equal(indices_, rhs.indices_)) return false;
//		if (!Utility::equal(mat_, rhs.mat_)) return false;
//		return true;
//	}
//
//	void RMesh::dump_impl(ofstream& ofs, Dumper& dumper) const {
//		RObject::dump_impl(ofs, dumper);
//		dumper.write_vector(vertices_, ofs);
//		dumper.write_vector(indices_, ofs);
//		dumper.write_nested_obj(mat_, ofs);
//	}
//
//	void RMesh::load_impl(ifstream& ifs, Loader& loader) {
//		RObject::load_impl(ifs, loader);
//		loader.read_vector(vertices_, ifs);
//		loader.read_vector(vertices_, ifs);
//		mat_ = pcast<Material>(loader.read_nested_obj(ifs));
//	}
//
//	/****************** RShader ********************/
//	bool RShader::operator==(const RShader& rhs) {
//		if (!RObject::operator==(rhs)) return false;
//		return true;
//	}
//
//	void RShader::dump_impl(ofstream& ofs, Dumper& dumper) const {
//		RObject::dump_impl(ofs, dumper);
//
//	}
//
//	void RShader::load_impl(ifstream& ifs, Loader& loader) {
//		RObject::load_impl(ifs, loader);
//
//	}
//
//
//	/****************** RProgram ********************/
//	bool RProgram::operator==(const RProgram& rhs) {
//		if (!RObject::operator==(rhs)) return false;
//		return true;
//	}
//
//	void RProgram::dump_impl(ofstream& ofs, Dumper& dumper) const {
//		RObject::dump_impl(ofs, dumper);
//
//	}
//
//	void RProgram::load_impl(ifstream& ifs, Loader& loader) {
//		RObject::load_impl(ifs, loader);
//
//	}
//
//	/****************** RUniform ********************/
//	bool RUniform::operator==(const RUniform& rhs) {
//		if(!RObject::operator==(rhs)) return false;
//		return true;
//	}
//
//	void RUniform::dump_impl(ofstream& ofs, Dumper& dumper) const {
//		RObject::dump_impl(ofs, dumper);
//	}
//
//	void RUniform::load_impl(ifstream& ifs, Loader& loader) {
//		RObject::load_impl(ifs, loader);
//	}
//
//	/****************** RUniform ********************/
//
//
//	Resource::Resource(const string& name)
//	:Object(name){
//	}
//
//	bool Resource::operator==(const Resource& rhs) {
//		return Object::operator==(rhs) &&
//			Utility::equal(source_, rhs.source_) &&
//			Utility::equal(dump_dir_, rhs.dump_dir_);
//	}
//
//	void Resource::dump_impl(ofstream& ofs, Dumper& dumper) const{
//		Object::dump_impl(ofs, dumper);
//		dumper.write_basic(source_.u8string(), ofs);
//		dumper.write_basic(dump_dir_.u8string(), ofs);
//	}
//
//	void Resource::load_impl(ifstream& ifs, Loader& loader){
//		Object::load_impl(ifs, loader);
//		source_ = loader.read_basic<string>(ifs);
//		dump_dir_ = loader.read_basic<string>(ifs);
//	}
//
//	Shader::Shader(const string& name)
//		:Resource(name){
//	}
//
//	void Shader::dump_impl(ofstream& ofs, Dumper& dumper) const{
//	}
//
//	void Shader::load_impl(ifstream& ifs, Loader& loader){
//	}
//
//	Tex2d::Tex2d(const string& name){
//	}
//
//	shared_ptr<Tex2d> Tex2d::MakeTex(fs::path src_path)
//	{
//		return shared_ptr<Tex2d>();
//	}
//
//}