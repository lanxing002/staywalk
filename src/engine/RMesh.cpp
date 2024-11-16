#include "RMesh.h"
using namespace staywalk;
RMesh::RMesh(const string& name)
	:RObject(name) {

}

RMesh::RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name) 
	:RObject(name), vertices(vv), indices(ii){
}

void staywalk::RMesh::organize(){
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

void staywalk::RMesh::disband(){
}

bool staywalk::RMesh::load_resource(){
	return vertices.size() > 0 && indices.size() > 0;
}
