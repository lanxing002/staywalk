#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"
namespace staywalk {
	class sw_Class Actor : public GameObject{
	public:
	 	sw_Func Actor(const string& name = "0-actor");
		sw_Func void tick(float delta) override;
		
		sw_Prop shared_ptr<StaticMeshComponent> sm_comp{ nullptr };

		sw_Prop StaticMeshComponent ssm_comp;
		virtual void construct_ui();
		MetaRegister(Actor);
	};

	using PActor = shared_ptr<Actor>;
}


