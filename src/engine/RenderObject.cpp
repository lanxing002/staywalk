#include "RenderObject.h"
#include "Utility.h"
#include "Material.h"

namespace staywalk {
	Resource::Resource(const string& name)
		:Object(name){
	}

	Shader::Shader(const string& name)
		:Resource(name){
	}

	Tex2d::Tex2d(const string& name)
		:Resource(name){
	}

	RObject::RObject(const string& name)
		: Object(name) {
	}
}