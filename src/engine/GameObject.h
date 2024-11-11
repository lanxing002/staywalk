#pragma once
#include "Object.h"
#include "Common.h"

namespace staywalk
{
	class sw_Class GameObject : public Object
	{
	public:
		sw_Func GameObject(const string& name = "0-game-obj")
			:Object(name) {}

		sw_Func virtual void tick(float delta) {}

		sw_Prop vec3 location{ 0.0f };
		sw_Prop vec3 scale{ 1.0f };
		sw_Prop quat rotation{.0f, .0f, .0f, 1.f};
	};
}


