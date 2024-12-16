#include "RenderTarget.h"
#include "Utility.h"
#include "Engine.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"

namespace staywalk {
	RenderTarget::RenderTarget(const string& name)
		: Entity(name){
	}

	void RenderTarget::tick(float delta) {
		//if (sm_comp_) sm_comp_->tick(delta);
		//if (skeleton_comp_) skeleton_comp_->tick(delta);
	}
	

	void RenderTarget::use(){

	}

}

