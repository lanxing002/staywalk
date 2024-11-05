#include "Actor.h"
#include "Utility.h"
#include "Engine.h"

namespace staywalk {
	Actor::Actor() {
	}

	void Actor::tick(float delta) {
	}

	bool Actor::operator==(const Actor& rhs) {
		if (this == &rhs) return true;
		if (!GameObject::operator==(rhs)) return false;
		if (name_ != rhs.name_) return false;
		if (Utility::euqals(sm_comp_, rhs.sm_comp_)) return false;
		return true;
	}

	void Actor::dump(ofstream& ofs, Dumper& dumper){
		GameObject::dump(ofs, dumper);
		auto check_r = Utility::check_ofstream(ofs);
		assert(check_r);

		Utility::write_to_stream(name_, ofs);
		if(sm_comp_){
			Utility::write_to_stream(sm_comp_->get_guid(), ofs);
			dumper.dump_in_file(sm_comp_);
		}
		else {
			Utility::write_to_stream(kInvalidId, ofs);
		}
	}

	shared_ptr<Actor> Actor::load(ifstream& ifs, Loader& loader){
		auto result = std::make_shared<Actor>();
		Actor::placement_load(result, ifs, loader);
		return result;
	}

	void Actor::placement_load(shared_ptr<Actor> obj, ifstream& ifs, Loader& loader){
		GameObject::placement_load(obj, ifs);
		auto check_r = Utility::check_ifstream(ifs);
		assert(check_r);

		decltype(obj->name_.size()) name_len;
		ifs.read(reinterpret_cast<char*>(&name_len), sizeof name_len);
		obj->name_.resize(name_len);
		ifs.read((obj->name_.data()), name_len);

		idtype sm_comp_id = kInvalidId;
		ifs.read(reinterpret_cast<char*>(&sm_comp_id), sizeof sm_comp_id);
		if (sm_comp_id != kInvalidId) {
			ObjectType ot;
			obj->sm_comp_ = std::dynamic_pointer_cast<StaticMeshComponent>(loader.load_in_file(sm_comp_id, ot));
			assert(ot == ObjectType::StaticMeshComponent);
		}

		return;
	}
}

