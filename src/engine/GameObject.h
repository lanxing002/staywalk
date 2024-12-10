#pragma once
#include "Object.h"
#include "SimpleType.h"
#include "Common.h"

namespace staywalk
{
	class sw_Class()  GameObject : public Object
	{
	public:
		sw_Func()  GameObject(const string& name = "0-game-obj")
			:Object(name) {}
		sw_Prop() Transform transform_ = Identity;
		MetaRegister(GameObject);

		//---------------------------------//
		virtual void tick(float delta) {}
	};
}


