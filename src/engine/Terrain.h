#pragma once
#include "Actor.h"


namespace staywalk {
	class sw_Class()  Terrain : public Actor{
	public:
	 	sw_Func()  Terrain(const string& name = "0-actor");
		
		sw_Func() void init_with_plane();

		void tick(float delta) override;

		MetaRegister(Terrain);

	private:
		AABB aabb_;
	};
}


