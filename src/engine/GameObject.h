#pragma once
#include "Object.h"
#include "Common.h"

namespace staywalk
{
	class sw_Class()  GameObject : public Object
	{
	public:
		sw_Func()  GameObject(const string& name = "0-game-obj")
			:Object(name) {}

		virtual void tick(float delta) {}

		sw_Prop() Transform transform = Identity;

		MetaRegister(GameObject);
	};
}


