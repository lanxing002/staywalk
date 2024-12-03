#pragma once
#include "GameObject.h"

namespace staywalk {
	class sw_Class()  Actor : public GameObject{
	public:
	 	sw_Func()  Actor(const string& name = "0-actor");
		
		void tick(float delta) override;

		sw_Prop() StaticMeshComponentRef sm_comp{ nullptr };
		sw_Prop() AABB get_aabb();

		sw_Prop() 

		MetaRegister(Actor);

	private:
		AABB aabb_;
	};
}


