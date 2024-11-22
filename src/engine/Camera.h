#pragma once
#include "GameObject.h"
#include "Common.h"

namespace staywalk{
	class sw_Class() Camera : public GameObject{
	public:
		sw_Func()  Camera(const string& name = "camera-0");

		MetaRegister(Camera);
	};
}


