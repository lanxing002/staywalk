#include "RMesh.h"
using namespace staywalk;
RMesh::RMesh(const string& name)
	:RObject(name) {

}

RMesh::RMesh(const vector<Vertex>& vv, const vector<unsigned int>& ii, const string& name) 
	:RObject(name), vertices(vv), indices(ii){

}