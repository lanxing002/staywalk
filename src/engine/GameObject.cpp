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

	void GameObject::dump(ofstream& ofstrm){
		Object::dump(ofstrm);
		auto check_r = Utility::check_ofstream(ofstrm);
		assert(check_r);
		ofstrm.write(reinterpret_cast<char*>(&location_), sizeof location_);
		ofstrm.write(reinterpret_cast<char*>(&scale_), sizeof scale_);
		ofstrm.write(reinterpret_cast<char*>(&rotation_), sizeof rotation_);
	}

	//shared_ptr<GameObject> GameObject::load(ifstream& ifs){
	//	auto result = std::make_shared<GameObject>();
	//	GameObject::placement_load(result, ifs);
	//	return result;
	//}

	void GameObject::placement_load(shared_ptr<GameObject> obj, ifstream& ifs){
		Object::placement_load(obj, ifs);
		auto check_r = Utility::check_ifstream(ifs);
		assert(check_r);
		ifs.read(reinterpret_cast<char*>(&obj->location_), sizeof obj->location_);
		ifs.read(reinterpret_cast<char*>(&obj->scale_), sizeof obj->scale_);
		ifs.read(reinterpret_cast<char*>(&obj->rotation_), sizeof obj->rotation_);
	}
}

