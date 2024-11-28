#include "RMesh.h"
#include "Utility.h"

using namespace staywalk;
RMesh::RMesh(const string& name)
	:RObject(name) {

}

RMesh::RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name) 
	: RObject(name), vertices(vv), indices(ii){
}

void RMesh::organize(){
	if (!load_resource()) return;

	glGenVertexArrays(1, &glid);
	glBindVertexArray(glid);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	constexpr auto vertex_size = sizeof(decltype(vertices)::value_type);
	auto size_byte = vertices.size() * vertex_size;
	glBufferData(GL_ARRAY_BUFFER, size_byte, vertices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
	
	glEnableVertexAttribArray(1); // normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2); // texcoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(3); // tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(8 * sizeof(float)));

	glEnableVertexAttribArray(4); // bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(11 * sizeof(float)));
}

void RMesh::disband(){

}

bool RMesh::load_resource(){
	return vertices.size() > 0 && indices.size() > 0;
}

void RMesh::load_post() {
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
	log(fmt::format("load_post to {}, status: {}", path.u8string(), status),
		status ? LogLevel::Info : LogLevel::Warn);
}

void RMesh::dump_post() const {
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
