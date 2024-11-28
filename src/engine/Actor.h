#pragma once
#include "GameObject.h"
#include "StaticMeshComponent.h"
namespace staywalk {
	class sw_Class()  Actor : public GameObject{
	public:
	 	sw_Func()  Actor(const string& name = "0-actor");
		sw_Func(nopy;)  void tick(float delta) override;
		
		sw_Prop() shared_ptr<StaticMeshComponent> sm_comp{ nullptr };

		sw_Prop() StaticMeshComponent ssm_comp;

		sw_Prop() ShaderType shader_type = ShaderType::VS;

		MetaRegister(Actor);
	};

	using ActorRef = shared_ptr<Actor>;
}


