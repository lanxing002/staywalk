#include "Renderer.h"
#include "Engine.h"
#include "Actor.h"
#include "World.h"
#include "StaticMeshComponent.h"

using namespace staywalk;


RProgramRef Renderer::query_program(ProgramType pt){
	return program_table_[(int)pt];
}

void Renderer::initialize(){

}

void Renderer::render(double delta, unsigned long long count)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the 

	auto engine = Engine::get_engine();
	auto world = engine->get_world();
	if (world == nullptr) return;

	// light mgr
	{
		auto& lights = world->get_lights();
		auto& buffer = light_mgr_.light_buffer;
		auto num = std::min((unsigned int)lights.size(), RLight::kMaxLights);
		int real_count = 0;
		for (int i = 0; i < num; i++) {
			if (lights[i] == nullptr) continue;
			real_count++;
			buffer.light_data[i].position = lights[i]->transform.location;
		}
		buffer.light_count = real_count;
	}

	RenderInfo render_info;
	if (auto cam = world->get_activated_camera()) {
		render_info.view = cam->view;
		render_info.projection = cam->projection;
	}
	
	// render mesh
	{
		for (auto& actor : world->get_actors()) {
			if (nullptr == actor->sm_comp) continue;
			actor->sm_comp->draw(render_info);
		}
	}
}
