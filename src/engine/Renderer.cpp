#include "Renderer.h"
#include "Engine.h"
#include "Actor.h"
#include "World.h"
#include "RProgram.h"
#include "RenderTarget.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"
#include "Material.h"

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
	stateset_ = std::make_shared<StateSet>("std");

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::render(double delta, unsigned long long count)
{
	auto engine = Engine::get_engine();
	auto world = engine->get_world();
	if (world == nullptr) return;

	vector<RenderTargetRef> post;
	const auto& rts = world->get_all_rendertargets();
	const auto rt_num = rts.size();
	const auto& light = world->get_main_light();
	vec4 light_vec = vec4(light->pos.x, light->pos.y, light->pos.z,
		light->light_type_ == LightType::Directional ? 1.0 : -1.0);
	
	for (size_t idx = 0; idx <= rt_num; idx++) {
		bool main_pass = idx == rt_num;
		if (main_pass) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);  // default framebuffer
			glViewport(0, 0, engine->get_view_size().x, engine->get_view_size().y);
		}
		else{
			if (rts[idx] == nullptr) continue;
			if (rts[idx]->post_stage_) { post.push_back(rts[idx]); continue; }
			rts[idx]->use();
		}

		GLCheck(;);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLCheck(;);
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
		render_info.stateset_ = stateset_;
		if (main_pass) {
			if (auto cam = world->get_activated_camera()) {
				render_info.view_.top() = cam->view_;
				render_info.projection_.top() = cam->projection_;
			}
		}
		else {
			render_info.view_.top() = rts[idx]->camera_.view_;
			render_info.projection_.top() = rts[idx]->camera_.projection_;
		}

		auto program = program_table_[(int)ProgramType::PBR];
		if (!main_pass && rts[idx]->program_) program = rts[idx]->program_;
		render_info.program_ = program;
		
		// setup shader
		static UniformRef false_uniform = std::make_shared<Uniform>(0);
		static UniformRef true_uniform = std::make_shared<Uniform>(1);
		render_info.stateset_->add_uniform("light", std::make_shared<Uniform>(light_vec));
		// render mesh
		{
			GLCheck(;);
			render_info.stateset_->add_uniform("use_skeleton", false_uniform);
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
			render_info.stateset_->add_uniform("use_skeleton", true_uniform);
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
}

staywalk::Renderer::~Renderer(){

}

void staywalk::Renderer::destroy(){
	Program::monitor(program_table_[static_cast<int>(ProgramType::PBR)], false);
	Program::monitor(program_table_[static_cast<int>(ProgramType::Shadow)], false);
	for (int i = 0; i < (int)ProgramType::_Count; i++)
		program_table_[i] = nullptr;
}
