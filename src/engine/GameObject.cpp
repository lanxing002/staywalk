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

	void GameObject::dump(ofstream& ofs, Dumper& dumper){
		Object::dump(ofs, dumper);
		auto check_r = Utility::check_ofstream(ofs);
		assert(check_r);
		Utility::write_to_stream(location_, ofs);
		Utility::write_to_stream(scale_, ofs);
		Utility::write_to_stream(rotation_, ofs);
	}

	shared_ptr<GameObject> GameObject::load(ifstream& ifs, Loader& loader){
		auto result = std::make_shared<GameObject>();
		GameObject::placement_load(result, ifs);
		return result;
	}

	void GameObject::placement_load(shared_ptr<GameObject> obj, ifstream& ifs){
		Object::placement_load(obj, ifs);
		auto check_r = Utility::check_ifstream(ifs);
		assert(check_r);
		obj->location_ =  Utility::load_from_stream<vec3>(ifs);
		obj->scale_ =  Utility::load_from_stream<vec3>(ifs);
		obj->rotation_ =  Utility::load_from_stream<quat>(ifs);
	}
}

