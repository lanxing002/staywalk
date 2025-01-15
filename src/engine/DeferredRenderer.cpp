#include "DeferredRenderer.h"
#include "Engine.h"
#include "Actor.h"
#include "World.h"
#include "RProgram.h"
#include "RenderTarget.h"
#include "StaticMeshComponent.h"
#include "SkeletonMeshComponent.h"
#include "DepthRenderTarget.h"
#include "Material.h"
#include "reflect.h"

using namespace staywalk;

staywalk::DeferredRenderer::DeferredRenderer(){
	gbuffer_ = std::make_shared<GBuffer>();
}

staywalk::DeferredRenderer::~DeferredRenderer() {

}

void DeferredRenderer::initialize(){
	Renderer::initialize();
}

void DeferredRenderer::render(double delta, unsigned long long count)
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

	mat4 light_view_project = mat4(1.0);
	Tex2DRTRef shadow_tex = 0;
	
	for (size_t idx = 0; idx <= rt_num; idx++) {
		RenderInfo render_info;
		auto program = program_table_[(int)ProgramType::PBR];
		bool main_pass = idx == rt_num;
		
		{ // construct renderinfo
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

			if (!main_pass && rts[idx]->program_) program = rts[idx]->program_;
			render_info.program_ = program;
		}
		
		// set up frambe buffer
		if (main_pass) {
			gbuffer_->set_size(engine->get_view_size().x, engine->get_view_size().y);
			gbuffer_->bind();
		}
		else{
			if (rts[idx] == nullptr) continue;
			if (rts[idx]->post_stage_) { post.push_back(rts[idx]); continue; }
			if (rts[idx]->get_meta_info().tname == "staywalk::DepthRenderTarget") {
				light_view_project =  rts[idx]->camera_.projection_ * rts[idx]->camera_.view_;
				shadow_tex = pcast<DepthRenderTarget>(rts[idx])->depth_rt_;
			}
			rts[idx]->bind();
		}

		// clear framebuffer
		GLCheck(;);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLCheck(;);
		
		// setup uniform about shadow
		{
			render_info.stateset_->add_uniform("u_light", std::make_shared<Uniform>(light_vec));
			render_info.stateset_->add_uniform("u_light_view_project", std::make_shared<Uniform>(light_view_project));
			if (main_pass) {
				render_info.stateset_->add_tex("shadow", shadow_tex);
			}
		}

		// render mesh
		{
			static UniformRef false_uniform = std::make_shared<Uniform>(0);
			static UniformRef true_uniform = std::make_shared<Uniform>(1);
			
			GLCheck(;);
			render_info.stateset_->add_uniform("u_use_skeleton", false_uniform);
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
			render_info.stateset_->add_uniform("u_use_skeleton", true_uniform);
			for (auto& actor : world->get_actors()) {
				render_info.model_.top() = actor->transform_.matrix();
				if (actor->skeleton_comp_) actor->skeleton_comp_->draw(render_info);
			}

			assert(
				render_info.program_ == program
				&& render_info.model_.size() == 1
				&& render_info.projection_.size() == 1
				&& render_info.view_.size() == 1);
		}

		if (main_pass) {
			// use gbuffer render to default framebuffer
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);  // gbuffer
}

void staywalk::DeferredRenderer::destroy(){
	Renderer::destroy();
}
