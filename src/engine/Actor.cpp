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
		dumper.write_nested_obj(sm_comp_, ofs);
	}

	void Actor::load_impl(ifstream& ifs, Loader& loader){
		GameObject::load_impl(ifs, loader);
		sm_comp_ = std::dynamic_pointer_cast<StaticMeshComponent>(loader.read_nested_obj(ifs)); // TODO:
	}
}

