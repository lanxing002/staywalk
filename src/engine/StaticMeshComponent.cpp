#include "StaticMeshComponent.h"
#include "Utility.h"

namespace staywalk {
	StaticMeshComponent::StaticMeshComponent(const string& name)
		:GameComponent(name) {
	}

	void StaticMeshComponent::draw() {
		for (auto& [mesh, mat] : meshs) {
			if(mat) mat->use();
			if(mesh) mesh->draw();
		}
	}
}