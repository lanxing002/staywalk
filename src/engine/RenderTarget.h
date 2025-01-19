#pragma once
#include "Entity.h"
#include "Camera.h"
#include "RenderObject.h"

namespace staywalk {
	class sw_Class()  RenderTarget : public Entity {
	public:
	 	sw_Func()  RenderTarget(const string& name = "0-actor");
		sw_Prop() Camera camera_;
		sw_Prop() bool post_stage_ = false;
		sw_Prop() int width_ = 1024;
		sw_Prop() int height_ = 1024;
		sw_Prop() StdProgramRef  program_;
		MetaRegister(RenderTarget);

		//--------------------------------//
		void tick(float delta) override;
		virtual void bind() {}

	protected:
		FrameBufferRef framebuffer_;
	};
}


