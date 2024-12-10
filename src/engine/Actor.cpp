#include "Actor.h"
#include "Utility.h"
#include "Engine.h"
#include "StaticMeshComponent.h"

namespace staywalk {
	Actor::Actor(const string& name)
		: GameObject(name){
	}

	void Actor::tick(float delta) {
		if (sm_comp_) sm_comp_->tick(delta);
	}
	
	AABB Actor::get_aabb(){
		auto mat = transform_.matrix();
		AABB aabb;
		if (sm_comp_) {
			auto sm_aabb = sm_comp_->get_aabb();
			if (!sm_aabb.valid()) return aabb;
			aabb.expand(mat * vec4(sm_aabb.min, 1.0));
			aabb.expand(mat * vec4(sm_aabb.max, 1.0));
		}
		return aabb;
	}

}

