#pragma once
#include "Actor.h"

namespace staywalk {
	class sw_Class()  Skybox : public Actor{
	public:
	 	sw_Func()  Skybox(const string& name = "skybox");
		sw_Func() static Ref<Skybox> create(const string & name = "skybox");

		MetaRegister(Skybox);

		//--------------------------------//
		void tick(float delta) override;
	};
}


