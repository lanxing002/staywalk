#include "DepthRenderTarget.h"
#include "Utility.h"
#include "Engine.h"
#include "World.h"
#include "RProgram.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"
#include "Actor.h"

namespace staywalk {
	DepthRenderTarget::DepthRenderTarget(const string& name)
		: RenderTarget(name){
		rt_ = std::make_shared<RenderTarget2D>("depth");
	}
	
	DepthRenderTarget::~DepthRenderTarget() {
		if (program_) StdProgram::monitor(program_, false);
	}

	void DepthRenderTarget::bind(){
		rt_->bind();
	}

	void DepthRenderTarget::tick(float delte) {
		auto world = Engine::get_world();
		if (world != nullptr) {
			auto look_pos = glm::vec3(0.0);
			auto actors = world->get_actors();
			if (actors.size() > 0 && actors[0])
				look_pos = actors[0]->transform_.location;
			camera_.view_ = glm::lookAt(camera_.transform_.location, look_pos, glm::vec3(0.0, 0.0, 1.0));
			camera_.projection_ = glm::perspective(glm::radians(camera_.fov_), camera_.aspect_, camera_.near_, camera_.far_);

			const auto& light = world->get_main_light();
			if (light) light->pos = glm::normalize(camera_.transform_.location - look_pos);
		}
	}


	void DepthRenderTarget::dump_post() const {

	}
	
	void DepthRenderTarget::load_post() {
		rt_->resize(width_, height_);
		rt_->set_comp_flag(RTComp::DEPTH);
		//rt_->wrap_s_ = GlWrap::REPEAT;
		//rt_->wrap_t_ = GlWrap::REPEAT;
		if (program_) StdProgram::monitor(program_, true);
	}
}

