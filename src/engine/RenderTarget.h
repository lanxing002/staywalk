#pragma once
#include "Entity.h"
#include "Camera.h"
#include "RenderObject.h"

namespace staywalk {
	class sw_Class(jsonpost;)  RenderTarget : public Entity {
	public:
	 	sw_Func()  RenderTarget(const string& name = "0-actor");
		sw_Prop() Camera camera_;
		sw_Prop() bool post_stage_ = false;
		sw_Prop() int width_ = 1024;
		sw_Prop() int height_ = 1024;
		sw_Prop() Tex2DRTRef color_rt_;
		sw_Prop() Tex2DRTRef depth_rt_;
		sw_Prop() Tex2DRTRef stencil_rt_;
		sw_Prop() ProgramRef  program_;
		MetaRegister(RenderTarget);
		//--------------------------------//
		void tick(float delta) override;
		void use();

	private:
		void dump_post() const;
		void load_post();

	private:
		FrameBufferRef framebuffer_;
	};
}


