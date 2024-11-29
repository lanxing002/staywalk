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

		void tick(float delta) override;

		sw_Prop() ProjectType porject_type;
		sw_Prop() float fov{60.0f};
		sw_Prop() float aspect{1.0f};
		sw_Prop() float near{0.1f};
		sw_Prop() float far{ 1000.0f };

		mat4 view;
		mat4 projection;

		MetaRegister(Camera);
	};
}


