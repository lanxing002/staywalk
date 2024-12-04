#include "RMesh.h"
#include "Utility.h"

using namespace staywalk;
Mesh::Mesh(const string& name)
	:RObject(name) {

}

Mesh::Mesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name) 
	: RObject(name), vertices(vv), indices(ii){
}

void Mesh::organize(){
	if (!load_resource()) return;

	glGenVertexArrays(1, &glid);
	glBindVertexArray(glid);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	constexpr auto vertex_size = sizeof(decltype(vertices)::value_type);
	auto size_byte = vertices.size() * vertex_size;
	glBufferData(GL_ARRAY_BUFFER, size_byte, vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	constexpr int dd = sizeof(decltype(indices)::value_type);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
	
	glEnableVertexAttribArray(1); // normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(2); // texcoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, texcoords));

	glEnableVertexAttribArray(3); // tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, tangent));

	glEnableVertexAttribArray(4); // bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)offsetof(Vertex, bitangent));
	glBindVertexArray(0);
}

void Mesh::disband(){
	disband_impl();
}

bool Mesh::load_resource(){
	return vertices.size() > 0 && indices.size() > 0;
}

void Mesh::load_post() {
	auto path = Utility::get_objects_dir() / (name + Utility::kMeshExt);
	auto ifs = ifstream(path, std::ios::binary);
	bool status = false;
	if (ifs) {
		size_t vsize = 0;
		size_t isize = 0;

		ifs.read(reinterpret_cast<char*>(&vsize), sizeof(vsize));
		ifs.read(reinterpret_cast<char*>(&isize), sizeof(isize));

		vertices.resize(vsize);
		indices.resize(isize);

		ifs.read(reinterpret_cast<char*>(vertices.data()), vsize * sizeof(Vertex));
		ifs.read(reinterpret_cast<char*>(indices.data()), isize * sizeof(unsigned int));
		status = true;
	}
	compute_aabb();
	log(fmt::format("load_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
}

void Mesh::dump_post() const {
	size_t vsize = vertices.size();
	size_t isize = indices.size();
	auto path = Utility::get_objects_dir() / (name + Utility::kMeshExt);
	auto ofs = ofstream(path, std::ios::binary | std::ios::trunc);
	bool status = false;
	if (ofs) {
		ofs.write(reinterpret_cast<char*>(&vsize), sizeof(vsize));
		ofs.write(reinterpret_cast<char*>(&isize), sizeof(isize));

		ofs.write(reinterpret_cast<const char*>(vertices.data()), vsize * sizeof(Vertex));
		ofs.write(reinterpret_cast<const char*>(indices.data()), isize * sizeof(unsigned int));
		status = true;
	}

	log(fmt::format("dump_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
}

staywalk::AABB staywalk::Mesh::get_aabb(){
	return aabb_;
}

staywalk::AABB staywalk::Mesh::compute_aabb() {
	for (const auto& v : vertices)
		aabb_.expand(v.position);
	return aabb_;
}

staywalk::MeshRef staywalk::Mesh::create_simple_mesh(){
	auto result = std::make_shared<Mesh>();
	Vertex v1;
	Vertex v2; 
	Vertex v3;
	Vertex v4;
	v1.position = vec3(-0.5, 0.0, 0.0);
	v2.position = vec3(0.5, 0.0, 0.0);
	v3.position = vec3(0.0, 1.0, 0.0);
	v4.position = vec3(0.0, 0.0, 1.0);

	result->vertices = vector<Vertex>{ v1, v2, v3, v4 };
	result->indices = vector<unsigned int>{0, 1, 2, 0, 1, 3};
	result->compute_aabb();
	return result;
}

staywalk::Mesh::~Mesh()
{
	if (valid()) disband_impl();
}

void staywalk::Mesh::draw(RenderInfo& info) {
	if (!valid()) organize();
	glBindVertexArray(glid);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void staywalk::Mesh::disband_impl(){
	glid = kGlSickId;
}
