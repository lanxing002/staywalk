#include "RenderTarget.h"
#include "Utility.h"
#include "Engine.h"
#include "World.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"

namespace staywalk {
	RenderTarget::RenderTarget(const string& name)
		: Entity(name){
		framebuffer_ = std::make_shared<FrameBuffer>("fb");
		color_rt_ = std::make_shared<Tex2DRT>("color");
		depth_rt_ = std::make_shared<Tex2DRT>("depth");
		stencil_rt_ = std::make_shared<Tex2DRT>("stencil");
	}

	void RenderTarget::tick(float delta) {
		auto world = Engine::get_world();
		if (world) {
			auto camera = world->get_activated_camera();
			if (camera) camera_ = *camera;
			camera_.aspect_ = width_ / (height_ + 0.000001f);
			camera_.update_matrix();
		}
	}
	

	void RenderTarget::use(){
		auto fbid = framebuffer_->get_updated_glid();
		glBindFramebuffer(GL_FRAMEBUFFER, fbid);
		if (color_rt_) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 
				color_rt_->get_updated_glid(), 0);
		}

		if (depth_rt_) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
				depth_rt_->get_updated_glid(), 0);
		}

		if (stencil_rt_) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
				stencil_rt_->get_updated_glid(), 0);
		}
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (color_rt_) glDrawBuffer(GL_COLOR_ATTACHMENT0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			log("RenderTarget:: not complete", LogLevel::Warn);
		glViewport(0, 0, width_, height_);
		GLCheck(;);
	}

	void RenderTarget::dump_post() const {

	}
	
	void RenderTarget::load_post() {
		if (color_rt_) {
			color_rt_->width_ = width_;
			color_rt_->height_ = height_;
			depth_rt_->mark_dirty();
		}

		if (depth_rt_) {
			depth_rt_->width_ = width_;
			depth_rt_->height_ = height_;
			depth_rt_->mark_dirty();
		}

		if (stencil_rt_) {
			stencil_rt_->width_ = width_;
			stencil_rt_->height_ = height_;
			depth_rt_->mark_dirty();
		}
	}
}

