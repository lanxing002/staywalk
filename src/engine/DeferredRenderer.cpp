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
	mainpass_gbuffer_ = std::make_shared<GBuffer>();
}

staywalk::DeferredRenderer::~DeferredRenderer() {

}

void DeferredRenderer::initialize(){
	Renderer::initialize();
}



void staywalk::DeferredRenderer::render_screen()
{
}

void staywalk::DeferredRenderer::render_custom_rt(RenderTargetRef rt){
	auto engine = Engine::get_engine();
	auto world = engine->get_world();

	RenderInfo render_info;
	render_info.model_.push(mat4(1.0));
	render_info.view_.push(mat4(1.0));
	render_info.projection_.push(mat4(1.0));
	render_info.stateset_ = stateset_;

	render_info.view_.top() = rt->camera_.view_;
	render_info.projection_.top() = rt->camera_.projection_;
	if(rt->program_) render_info.program_ = rt->program_;
	if (rt->get_meta_info().tname == "staywalk::DepthRenderTarget") {
		//light_view_project = rts[idx]->camera_.projection_ * rts[idx]->camera_.view_;
		//shadow_tex = pcast<DepthRenderTarget>(rts[idx])->depth_rt_;
	}
	
	rt->bind();
	// clear framebuffer
	GLCheck(;);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLCheck(;);

	// setup uniform about shadow
	{
		//render_info.stateset_->add_uniform("u_light", std::make_shared<Uniform>(light_vec));
		//render_info.stateset_->add_uniform("u_light_view_project", std::make_shared<Uniform>(light_view_project));
	}
	render_all_mesh(render_info);
}

void DeferredRenderer::render(double delta, unsigned long long count)
{
	auto engine = Engine::get_engine();
	auto world = engine->get_world();
	if (world == nullptr) return;

	vector<RenderTargetRef> post;
	const auto& rts = world->get_all_rendertargets();
	const auto rt_num = rts.size();
	vector<RenderTargetRef> post_rts;
	for (auto& rt : rts) {
		if (!rt) continue;
		if (rt->post_stage_) { 
			post_rts.push_back(rt); continue; 
		}

		render_custom_rt(rt);
	}

	render_main();

	for (auto& rt : post_rts)
		render_custom_rt(rt);

	render_post0();

	render_post1();

	render_screen();
}

void staywalk::DeferredRenderer::render_all_mesh(RenderInfo& render_info){
	// render mesh
	static UniformRef false_uniform = std::make_shared<Uniform>(0);
	static UniformRef true_uniform = std::make_shared<Uniform>(1);

	auto engine = Engine::get_engine();
	auto world = engine->get_world();

	GLCheck(;);
	render_info.stateset_->add_uniform("u_use_skeleton", false_uniform);
	for (auto& actor : world->get_actors()) {
		render_info.model_.top() = actor->transform_.matrix();
		if (actor->sm_comp_) actor->sm_comp_->draw(render_info);
	}
	
	auto program = render_info.program_;
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

void staywalk::DeferredRenderer::destroy(){
	Renderer::destroy();
}

void staywalk::DeferredRenderer::render_main(){

	Tex2DRTRef shadow_tex = 0;
	RenderInfo render_info;
	{
		render_info.model_.push(mat4(1.0));
		render_info.view_.push(mat4(1.0));
		render_info.projection_.push(mat4(1.0));
		render_info.stateset_ = stateset_;
	}

	//if (main_pass) {
	//	if (auto cam = world->get_activated_camera()) {
	//		render_info.view_.top() = cam->view_;
	//		render_info.projection_.top() = cam->projection_;
	//	}
	//}
}

void staywalk::DeferredRenderer::render_post0(){

}

void staywalk::DeferredRenderer::render_post1()
{
}

