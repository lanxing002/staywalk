#pragma once
#include "GameObject.h"
#include <array>

namespace staywalk {
	
	class sw_Class() Light : public GameObject {
	public:

		sw_Func() Light(const string& name = "light-0");

		void tick(float delta) override;

		MetaRegister(Light);
	};

}
