#pragma once
#include "Object.h"
namespace staywalk{
	class sw_Class()  GameComponent : public Object{
	public:
		sw_Func()  GameComponent(const string& name = "0-comp")
			:Object(name) {}

		MetaRegister(GameComponent);
	};
}

