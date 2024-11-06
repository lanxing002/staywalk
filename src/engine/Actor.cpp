#include "Actor.h"
#include "Utility.h"
#include "Engine.h"

namespace staywalk {
	Actor::Actor(const string& name)
		: GameObject(name){
	}

	void Actor::tick(float delta) {
	}

	bool Actor::operator==(const Actor& rhs) {
		if (this == &rhs) return true;
		if (!GameObject::operator==(rhs)) return false;
		if (name_ != rhs.name_) return false;
		if (!Utility::euqals(sm_comp_, rhs.sm_comp_)) return false;
		return true;
	}

	void Actor::dump(ofstream& ofs, Dumper& dumper){
		GameObject::dump(ofs, dumper);
		auto check_r = Utility::check_ofstream(ofs);
		assert(check_r);
		if(sm_comp_){
			Utility::write_to_stream(sm_comp_->get_guid(), ofs);
			dumper.dump_in_file(sm_comp_);
		}
		else {
			Utility::write_to_stream(kInvalidId, ofs);
		}
	}

	void Actor::placement_load(shared_ptr<Actor> obj, ifstream& ifs, Loader& loader){
		GameObject::placement_load(obj, ifs);
		auto check_r = Utility::check_ifstream(ifs);
		assert(check_r);
		idtype sm_comp_id = Utility::load_from_stream<idtype>(ifs);
		if (sm_comp_id != kInvalidId) {
			ObjectType ot;
			auto cc = loader.load_in_file(sm_comp_id, ot);
			auto dd = std::dynamic_pointer_cast<StaticMeshComponent>(cc);
			auto ccc = dynamic_cast<StaticMeshComponent*>(cc.get());
			obj->sm_comp_ = dd;
			assert(ot == ObjectType::StaticMeshComponent);
		}

		return;
	}
}

