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

	void Actor::dump_impl(ofstream& ofs, Dumper& dumper){
		GameObject::dump_impl(ofs, dumper);
		if(sm_comp_){
			Utility::write_to_stream(sm_comp_->get_guid(), ofs);
			dumper.dump_obj_in_file(sm_comp_);
		}
		else {
			Utility::write_to_stream(kInvalidId, ofs);
		}
	}

	void Actor::load_impl(shared_ptr<Actor> obj, ifstream& ifs, Loader& loader){
		GameObject::load_impl(obj, ifs, loader);
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

