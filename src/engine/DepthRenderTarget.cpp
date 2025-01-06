#include "DepthRenderTarget.h"
#include "Utility.h"
#include "Engine.h"
#include "World.h"
#include "RProgram.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"

namespace staywalk {
	DepthRenderTarget::DepthRenderTarget(const string& name)
		: RenderTarget(name){
		depth_rt_ = std::make_shared<Tex2DRT>("depth");
	}
	
	DepthRenderTarget::~DepthRenderTarget() {
		if (program_) Program::monitor(program_, false);
	}

	void DepthRenderTarget::use(){
		auto fbid = framebuffer_->get_updated_glid();
		glBindFramebuffer(GL_FRAMEBUFFER, fbid);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
			depth_rt_->get_updated_glid(), 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		//if (color_rt_) glDrawBuffer(GL_COLOR_ATTACHMENT0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			log("DepthRenderTarget:: not complete", LogLevel::Warn);
		glViewport(0, 0, width_, height_);
		GLCheck(;);
	}

	void DepthRenderTarget::tick(float delte) {
		auto world = Engine::get_world();
		if (world != nullptr) {
			const auto& light = world->get_main_light();
			auto look_pos = glm::vec3(0.0);
			if (light)
				look_pos = camera_.transform_.location + light->pos * 10.0f;
			camera_.view_ = glm::lookAt(camera_.transform_.location, look_pos, glm::vec3(0.0, 0.0, 1.0));
			camera_.projection_ = glm::perspective(glm::radians(camera_.fov_), camera_.aspect_, camera_.near_, camera_.far_);
		}
	}


	void DepthRenderTarget::dump_post() const {

	}
	
	void DepthRenderTarget::load_post() {
		depth_rt_->width_ = width_;
		depth_rt_->height_ = height_;
		depth_rt_->format_ = GlTexFormat::DEPTH;
		depth_rt_->wrap_s_ = GlWrap::REPEAT;
		depth_rt_->wrap_t_ = GlWrap::REPEAT;
		depth_rt_->min_filter_ = GlMinFilter::NEAREST;
		depth_rt_->mag_filter_ = GlMagFilter::NEAREST;
		depth_rt_->mark_dirty();

		if (program_) Program::monitor(program_, true);
	}
}

