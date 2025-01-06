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
}

