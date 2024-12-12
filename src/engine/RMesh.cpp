#include "RMesh.h"
#include "Utility.h"

using namespace staywalk;
Mesh::Mesh(const string& name)
	:RObject(name) {

	
}

Mesh::Mesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name) 
	: RObject(name), vertices_(vv), indices_(ii){
}

void Mesh::gl_update(){
	if (!(vertices_.size() > 0 && indices_.size() > 0)) return;
	glGenVertexArrays(1, &glid_);
	glBindVertexArray(glid_);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	constexpr auto vertex_size = sizeof(decltype(vertices_)::value_type);
	auto size_byte = vertices_.size() * vertex_size;
	glBufferData(GL_ARRAY_BUFFER, size_byte, vertices_.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	constexpr int dd = sizeof(decltype(indices_)::value_type);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(decltype(indices_)::value_type), indices_.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
	
	glEnableVertexAttribArray(1); // normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, normal_));

	glEnableVertexAttribArray(2); // texcoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, texcoords_));

	glEnableVertexAttribArray(3); // tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, tangent_));

	glEnableVertexAttribArray(4); // bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, bitangent_));
	glBindVertexArray(0);
}

void Mesh::gl_delete() {
	//disband_impl();
}

void Mesh::load_post() {
	auto path = Utility::get_objects_dir() / (name_ + Utility::kMeshExt);
	auto ifs = ifstream(path, std::ios::binary);
	bool status = false;
	if (ifs) {
		size_t vsize = 0;
		size_t isize = 0;

		ifs.read(reinterpret_cast<char*>(&vsize), sizeof(vsize));
		ifs.read(reinterpret_cast<char*>(&isize), sizeof(isize));

		vertices_.resize(vsize);
		indices_.resize(isize);

		ifs.read(reinterpret_cast<char*>(vertices_.data()), vsize * sizeof(Vertex));
		ifs.read(reinterpret_cast<char*>(indices_.data()), isize * sizeof(unsigned int));
		status = true;
	}
	compute_aabb();
	log(fmt::format("load_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
	mark_dirty();
}

void Mesh::dump_post() const {
	size_t vsize = vertices_.size();
	size_t isize = indices_.size();
	auto path = Utility::get_objects_dir() / (name_ + Utility::kMeshExt);
	auto ofs = ofstream(path, std::ios::binary | std::ios::trunc);
	bool status = false;
	if (ofs) {
		ofs.write(reinterpret_cast<char*>(&vsize), sizeof(vsize));
		ofs.write(reinterpret_cast<char*>(&isize), sizeof(isize));

		ofs.write(reinterpret_cast<const char*>(vertices_.data()), vsize * sizeof(Vertex));
		ofs.write(reinterpret_cast<const char*>(indices_.data()), isize * sizeof(unsigned int));
		status = true;
	}

	log(fmt::format("dump_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
}

staywalk::AABB staywalk::Mesh::get_aabb(){
	return aabb_;
}

staywalk::AABB staywalk::Mesh::compute_aabb() {
	for (const auto& v : vertices_)
		aabb_.expand(v.position_);
	return aabb_;
}

staywalk::MeshRef staywalk::Mesh::create_simple_mesh(){
	auto result = std::make_shared<Mesh>();
	Vertex v1;
	Vertex v2; 
	Vertex v3;
	Vertex v4;
	v1.position_ = vec3(-0.5, 0.0, 0.0);
	v2.position_ = vec3(0.5, 0.0, 0.0);
	v3.position_ = vec3(0.0, 1.0, 0.0);
	v4.position_ = vec3(0.0, 0.0, 1.0);

	result->vertices_ = vector<Vertex>{ v1, v2, v3, v4 };
	result->indices_ = vector<unsigned int>{0, 1, 2, 0, 1, 3};
	result->compute_aabb();
	return result;
}

staywalk::MeshRef staywalk::Mesh::create_plane(int row, int column){
	if (row < 1 || column < 1) {
		log(fmt::format("Mesh::create_plane failed --> wrong parameter: {}, {}", row, column), LogLevel::Error);
	}
	MeshRef result = std::make_shared<Mesh>("plane");
	float xstep = 1.0f / row;
	float ystep = 1.0f / column;
	
	for(int i = 0; i <= row; i++)
		for (int j = 0; j <= column; j++) {
			Vertex v;
			v.position_ = vec3(i * xstep, j * ystep, .0);
			v.normal_ = vec3(.0, .0, 1.0);
			v.texcoords_ = vec2(i * xstep, j * ystep);
			v.tangent_ = vec3(1.0, .0, .0);
			v.bitangent_ = vec3(.0, 1.0, .0);
			result->vertices_.push_back(v);
			if(i == 0 || j == 0) continue;
			//         a------b
			//         |      |
			//         d------c
			// c is current
			auto c_idx = j + (column + 1) * i;
			auto a_idx = (column + 1) * (i - 1) + j - 1;
			auto b_idx = a_idx + 1;
			auto d_idx = c_idx - 1;
			result->indices_.push_back(a_idx);
			result->indices_.push_back(b_idx);
			result->indices_.push_back(c_idx);
			result->indices_.push_back(a_idx);
			result->indices_.push_back(c_idx);
			result->indices_.push_back(d_idx);
		}

	return result;
}

staywalk::Mesh::~Mesh(){
 	gl_delete();
	//if (valid()) disband_impl();
}

void staywalk::Mesh::draw(RenderInfo& info) {
	if (dirty_) {
		gl_update();
		dirty_ = false;
	}
	if (!valid()) return;
	glBindVertexArray(glid_);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

SkeletonMesh::SkeletonMesh(const string& name /*= "smesh-0"*/)
	:RObject(name) {
}

SkeletonMesh::SkeletonMesh(const vector<SkinVertex>& vv, const vector<unsigned int>& ii, const string& name /*= "smesh-0"*/)
	:RObject(name), vertices_(vv), indices_(ii) {
}


void SkeletonMesh::load_post() {
	auto path = Utility::get_objects_dir() / (name_ + Utility::kMeshExt);
	auto ifs = ifstream(path, std::ios::binary);
	bool status = false;
	if (ifs) {
		size_t vsize = 0;
		size_t isize = 0;
		size_t msize = 0;

		ifs.read(reinterpret_cast<char*>(&vsize), sizeof(vsize));
		ifs.read(reinterpret_cast<char*>(&isize), sizeof(isize));
		ifs.read(reinterpret_cast<char*>(&msize), sizeof(msize));

		vertices_.resize(vsize);
		indices_.resize(isize);
		bone_mat_.resize(msize);

		ifs.read(reinterpret_cast<char*>(vertices_.data()), vsize * sizeof(Vertex));
		ifs.read(reinterpret_cast<char*>(indices_.data()), isize * sizeof(unsigned int));
		ifs.read(reinterpret_cast<char*>(bone_mat_.data()), msize * sizeof(mat4));
		status = true;
	}
	log(fmt::format("load_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
	mark_dirty();
}

void SkeletonMesh::dump_post() const {
	size_t vsize = vertices_.size();
	size_t isize = indices_.size();
	size_t msize = bone_mat_.size();
	auto path = Utility::get_objects_dir() / (name_ + Utility::kMeshExt);
	auto ofs = ofstream(path, std::ios::binary | std::ios::trunc);
	bool status = false;
	if (ofs) {
		ofs.write(reinterpret_cast<char*>(&vsize), sizeof(vsize));
		ofs.write(reinterpret_cast<char*>(&isize), sizeof(isize));
		ofs.write(reinterpret_cast<char*>(&msize), sizeof(msize));

		ofs.write(reinterpret_cast<const char*>(vertices_.data()), vsize * sizeof(Vertex));
		ofs.write(reinterpret_cast<const char*>(indices_.data()), isize * sizeof(unsigned int));
		ofs.write(reinterpret_cast<const char*>(bone_mat_.data()), isize * sizeof(mat4));
		status = true;
	}

	log(fmt::format("dump_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
}