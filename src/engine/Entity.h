#pragma once
#include "Object.h"
#include "SimpleType.h"
#include "Common.h"

namespace staywalk
{
	class sw_Class()  Entity : public Object
	{
	public:
		sw_Func()  Entity(const string& name = "0-game-obj")
			:Object(name) {}
		sw_Prop() Transform transform_ = Identity;
		MetaRegister(Entity);

		//---------------------------------//
		virtual void tick(float delta) {}
	};
}


