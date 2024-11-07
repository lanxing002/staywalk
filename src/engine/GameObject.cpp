#include "GameObject.h"
#include "Utility.h"

namespace staywalk {
	bool GameObject::operator==(const GameObject& gameobj) {
		if (!Object::operator==(gameobj)) return false;
		if (location_ != gameobj.location_) return false;
		if (scale_ != gameobj.scale_) return false;
		if (rotation_ != gameobj.rotation_) return false;
		return true;
	}

	void GameObject::dump_impl(ofstream& ofs, Dumper& dumper){
		Object::dump_impl(ofs, dumper);
		dumper.write_basic(location_, ofs);
		dumper.write_basic(scale_, ofs);
		dumper.write_basic(rotation_, ofs);
	}

	void GameObject::load_impl(ifstream& ifs, Loader& loader){
		Object::load_impl(ifs, loader);
		location_ = loader.read_basic<vec3>(ifs);
		scale_ = loader.read_basic<vec3>(ifs);
		rotation_ = loader.read_basic<quat>(ifs);
	}
}

