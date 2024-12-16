#pragma once
#include "Entity.h"
#include <array>

namespace staywalk {
	
	class sw_Class() RLight : public Entity {
	public:
		sw_Func() RLight(const string& name = "light-0");
		MetaRegister(RLight);

		void tick(float delta) override;
	};

}
