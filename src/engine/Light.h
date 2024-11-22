#pragma once
#include "GameObject.h"


namespace staywalk {
	class sw_Class() Light : public GameObject {
	public:
		sw_Func() Light(const string& name = "light-0");

		MetaRegister(Light);
	};
}
