#pragma once
#include "Entity.h"
#include <array>

namespace staywalk {

	enum class sw_Class() LightType : int {
		Directional = 0,
		Position = 1
	};

	class sw_Class() RLight : public Entity {
	public:
		sw_Func() RLight(const string& name = "light-0");
		sw_Prop() LightType light_type_ = LightType::Directional;
		sw_Prop() vec3 pos;
		MetaRegister(RLight);

		void tick(float delta) override;
	};

}
