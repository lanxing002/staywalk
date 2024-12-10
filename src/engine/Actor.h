#pragma once
#include "GameObject.h"

namespace staywalk {
	class sw_Class()  Actor : public GameObject{
	public:
	 	sw_Func()  Actor(const string& name = "0-actor");
		
		sw_Prop() StaticMeshComponentRef sm_comp_ { nullptr };
		sw_Func() AABB get_aabb();

		MetaRegister(Actor);

		//--------------------------------//
		void tick(float delta) override;

	private:
		AABB aabb_;
	};
}


