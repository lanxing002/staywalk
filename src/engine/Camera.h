#pragma once
#include "GameObject.h"
#include "Common.h"

namespace staywalk{
	enum class sw_Class() ProjectType : int {
		Persepective,
		Ortho,
	};

	class sw_Class() Camera : public GameObject{
	public:
		sw_Func()  Camera(const string& name = "camera-0");
		sw_Func() void look_actor(ActorRef actor);
		void tick(float delta) override;

		sw_Prop() ProjectType porject_type_;
		sw_Prop() float fov_{60.0f};
		sw_Prop() float aspect_{1.0f};
		sw_Prop() float near_{0.1f};
		sw_Prop() float far_{ 1000.0f };

		mat4 view_;
		mat4 projection_;

		MetaRegister(Camera);
	};
}


