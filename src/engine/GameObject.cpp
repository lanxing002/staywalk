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
		Utility::write_to_stream(location_, ofs);
		Utility::write_to_stream(scale_, ofs);
		Utility::write_to_stream(rotation_, ofs);
	}

	void GameObject::load_impl(shared_ptr<GameObject> obj, ifstream& ifs, Loader& loader){
		Object::load_impl(obj, ifs, loader);
		obj->location_ = Utility::load_from_stream<vec3>(ifs);
		obj->scale_ = Utility::load_from_stream<vec3>(ifs);
		obj->rotation_ = Utility::load_from_stream<quat>(ifs);
	}
}

