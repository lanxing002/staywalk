#include "GameObject.h"
#include "Utility.h"

namespace staywalk {
	bool GameObject::operator==(const GameObject& rhs) {
		return Object::operator==(rhs) &&
			Utility::equal(location_, rhs.location_) &&
			Utility::equal(scale_, rhs.scale_) &&
			Utility::equal(rotation_, rhs.rotation_);
	}

	void GameObject::dump_impl(ofstream& ofs, Dumper& dumper) const {
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

