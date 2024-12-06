#include "Renderer.h"
#include "Engine.h"
#include "Actor.h"
#include "World.h"
#include "RProgram.h"
#include "StaticMeshComponent.h"

using namespace staywalk;


RProgramRef Renderer::query_program(ProgramType pt){
	return program_table_[(int)pt];
}

void Renderer::initialize(){
	RProgramRef pbr = std::make_shared<RProgram>("pbr");
	RProgramRef shadow = std::make_shared<RProgram>("shadow");
	pbr->load_post();
	shadow->load_post();
	program_table_[static_cast<int>(ProgramType::PBR)] = pbr;
	program_table_[static_cast<int>(ProgramType::Shadow)] = shadow;

	RProgram::monitor(program_table_[static_cast<int>(ProgramType::PBR)]);
	RProgram::monitor(program_table_[static_cast<int>(ProgramType::Shadow)]);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		light_mgr_.sync_to_gpu();
	}

	RenderInfo render_info;
	render_info.model.push(mat4(1.0));
	render_info.view.push(mat4(1.0));
	render_info.projection.push(mat4(1.0));
	if (auto cam = world->get_activated_camera()) {
		render_info.view.top() = cam->view;
		render_info.projection.top() = cam->projection;
	}

	// setup shader
	{
		auto program = program_table_[(int)ProgramType::PBR];
		program->use();
		program->set_uniform("view", render_info.view.top());
		program->set_uniform("projection", render_info.projection.top());
		render_info.program = program;
	}
	
	// render mesh
	{
		for (auto& actor : world->get_actors()) {
			render_info.model.top() = actor->transform.matrix();
			if (nullptr == actor->sm_comp) continue;
			actor->sm_comp->draw(render_info);
		}
	}
}

staywalk::Renderer::~Renderer(){

}

void staywalk::Renderer::destroy(){
	RProgram::monitor(program_table_[static_cast<int>(ProgramType::PBR)], false);
	RProgram::monitor(program_table_[static_cast<int>(ProgramType::Shadow)], false);
}
