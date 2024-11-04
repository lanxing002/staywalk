#include "Actor.h"
#include "Utility.h"

namespace staywalk {
	Actor::Actor() {
	}

	Actor::~Actor() {
	}

	void Actor::tick(float delta) {
	}

	bool Actor::operator==(const Actor& rhs) {
		if (!GameObject::operator==(rhs)) return false;
		if (name_ != rhs.name_) return false;

		return true;
	}

	void Actor::dump(ofstream& ofs){
		GameObject::dump(ofs);
		auto check_r = Utility::check_ofstream(ofs);
		assert(check_r);

		const auto name_len = name_.size();
		ofs.write(reinterpret_cast<const char*>(&name_len), sizeof name_len);
		ofs.write(name_.c_str(), name_len);
		// TODO: dump shared_ptr for object
	}

	shared_ptr<Actor> Actor::load(ifstream& ifs){
		auto result = std::make_shared<Actor>();
		Actor::placement_load(result, ifs);
		return result;
	}

	void Actor::placement_load(shared_ptr<Actor> obj, ifstream& ifs){
		GameObject::placement_load(obj, ifs);
		auto check_r = Utility::check_ifstream(ifs);
		assert(check_r);

		decltype(obj->name_.size()) name_len;
		ifs.read(reinterpret_cast<char*>(&name_len), sizeof name_len);
		obj->name_.resize(name_len);

		ifs.read((obj->name_.data()), name_len);
		return;
	}
}

