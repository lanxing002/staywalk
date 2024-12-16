#pragma once
#include "Entity.h"
#include "Camera.h"
#include "RenderObject.h"

namespace staywalk {
	class sw_Class()  RenderTarget : public Entity{
	public:
	 	sw_Func()  RenderTarget(const string& name = "0-actor");
		sw_Prop() Camera camera_;
		sw_Prop() Tex2DRTRef tex_rt_;
		sw_Prop() GlAttachment attachment_ = GlAttachment::COLOR;
		MetaRegister(RenderTarget);
		//--------------------------------//
		void tick(float delta) override;
		void use();

	private:
		FrameBufferRef framebuffer_;
	};
}


