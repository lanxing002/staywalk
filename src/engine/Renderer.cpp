#include "Renderer.h"
#include "Engine.h"
#include "Actor.h"
#include "World.h"
#include "RProgram.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"

using namespace staywalk;


ProgramRef Renderer::query_program(ProgramType pt){
	return program_table_[(int)pt];
}

void Renderer::initialize(){
	ProgramRef pbr = std::make_shared<Program>("pbr");
	ProgramRef shadow = std::make_shared<Program>("shadow");
	pbr->load_post();
	shadow->load_post();
	program_table_[static_cast<int>(ProgramType::PBR)] = pbr;
	program_table_[static_cast<int>(ProgramType::Shadow)] = shadow;

	Program::monitor(program_table_[static_cast<int>(ProgramType::PBR)]);
	Program::monitor(program_table_[static_cast<int>(ProgramType::Shadow)]);

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
		auto num = (int)std::min((unsigned int)lights.size(), RenderLight::kMaxLights);
		int real_count = 0;
		for (int i = 0; i < num; i++) {
			if (lights[i] == nullptr) continue;
			real_count++;
			buffer.light_data[i].position = lights[i]->transform_.location;
		}
		buffer.light_count = real_count;
		light_mgr_.sync_to_gpu();
	}

	RenderInfo render_info;
	render_info.model_.push(mat4(1.0));
	render_info.view_.push(mat4(1.0));
	render_info.projection_.push(mat4(1.0));
	if (auto cam = world->get_activated_camera()) {
		render_info.view_.top() = cam->view_;
		render_info.projection_.top() = cam->projection_;
	}

	auto program = program_table_[(int)ProgramType::PBR];
	// setup shader
	program->use();
	program->set_uniform("view", render_info.view_.top());
	program->set_uniform("projection", render_info.projection_.top());
	render_info.program_ = program;
	
	// render mesh
	{
		GLCheck(;)
		program->set_uniform("use_skeleton", GL_FALSE);
		for (auto& actor : world->get_actors()) {
			render_info.model_.top() = actor->transform_.matrix();
			if (actor->sm_comp_) actor->sm_comp_->draw(render_info);
		}

		assert(
			render_info.program_ == program 
			&& render_info.model_.size() == 1
			&& render_info.projection_.size() == 1	
			&& render_info.view_.size() == 1);
		GLCheck(;);
		program->set_uniform("use_skeleton", GL_TRUE);
		for (auto& actor : world->get_actors()) {
			render_info.model_.top() = actor->transform_.matrix();
			if (actor->skeleton_comp_) actor->skeleton_comp_->draw(render_info);
		}

		GLCheck(;)
		assert(
			render_info.program_ == program
			&& render_info.model_.size() == 1
			&& render_info.projection_.size() == 1
			&& render_info.view_.size() == 1);
	}
}

staywalk::Renderer::~Renderer(){

}

void staywalk::Renderer::destroy(){
	Program::monitor(program_table_[static_cast<int>(ProgramType::PBR)], false);
	Program::monitor(program_table_[static_cast<int>(ProgramType::Shadow)], false);
	for (int i = 0; i < (int)ProgramType::_Count; i++)
		program_table_[i] = nullptr;
}
