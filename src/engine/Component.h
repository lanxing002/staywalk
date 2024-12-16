#pragma once
#include "Object.h"

namespace staywalk{
	class sw_Class()  Component : public Object{
	public:
		sw_Func()  Component(const string& name = "0-comp")
			:Object(name) {}
		MetaRegister(Component);

		//---------------------------------//
		virtual void tick(float delta) {}
	};
}

