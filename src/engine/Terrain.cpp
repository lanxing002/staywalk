#include "Terrain.h"
#include "Utility.h"
#include "Engine.h"
#include "StaticMeshComponent.h"

namespace staywalk {
	Terrain::Terrain(const string& name)
		: Actor(name){
	}

	void Terrain::init_with_plane()
	{
		auto mesh = Mesh::create_plane(100, 100);
		sm_comp = std::make_shared<StaticMeshComponent>("terrain-sm");
		sm_comp->add_mesh(mesh);
	}

	void Terrain::tick(float delta) {
		if (sm_comp) sm_comp->tick(delta);
	}
}

