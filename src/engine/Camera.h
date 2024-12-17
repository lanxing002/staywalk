#pragma once
#include "Entity.h"
#include "Common.h"

namespace staywalk{
	enum class sw_Class() ProjectType : int {
		Persepective,
		Ortho,
	};

	class sw_Class() Camera : public Entity{
	public:
		sw_Func()  Camera(const string& name = "camera-0");
		sw_Func() void look_actor(ActorRef actor);
		sw_Func() void update_matrix();

		sw_Prop() ProjectType porject_type_;
		sw_Prop() float fov_{60.0f};
		sw_Prop() float aspect_{1.0f};
		sw_Prop() float near_{0.1f};
		sw_Prop() float far_{ 1000.0f };
		MetaRegister(Camera);

		//---------------------------------//
		void tick(float delta) override;

		mat4 view_;
		mat4 projection_;

	};
}


