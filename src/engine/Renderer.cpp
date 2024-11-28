#include "Renderer.h"
#include "Engine.h"
#include "Actor.h"
#include "rhi.h"

using namespace staywalk;

void Renderer::render(double delta, unsigned long long count)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the 

	auto world = Engine::get_world();
	if (world == nullptr) return;
	// setup camera

	// setup light

	// render mesh
	{
		for (auto& actor : world->get_actors()) {
			if (nullptr == actor->sm_comp) continue;
			actor->sm_comp->draw();
		}
	}
}
