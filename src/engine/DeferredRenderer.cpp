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
#include "Logger.h"

using namespace staywalk;

staywalk::DeferredRenderer::DeferredRenderer(){
	mainpass_gbuffer_ = std::make_shared<GBuffer>();
	post_front_ = std::make_shared<RenderTarget2D>();
	post_back_ = std::make_shared<RenderTarget2D>();
	post_front_->format_ = GlTexFormat::RGBA;
	post_front_->internal_format_ = GlTexInternalFormat::RGBA;
	post_back_->format_ = GlTexFormat::RGBA;
	post_back_->internal_format_ = GlTexInternalFormat::RGBA;
	post_front_->set_comp_flag(RTComp::COLOR);
	post_back_->set_comp_flag(RTComp::COLOR);
}

staywalk::DeferredRenderer::~DeferredRenderer() {

}

void DeferredRenderer::initialize(){
	StdProgramRef pbr = std::make_shared<StdProgram>("pbr");
	StdProgramRef pbrpost = std::make_shared<StdProgram>("pbrpost");
	StdProgramRef shadow = std::make_shared<StdProgram>(shadow_name_);
	post_cs0_ = std::make_shared<CSProgram>("bloom");
	//post_cs1_ = std::make_shared<CSProgram>("");
	pbr->deferred_ = true;
	
	pbr->load_post();
	pbrpost->load_post();
	shadow->load_post();
	post_cs0_->load_post();

	program_table_[static_cast<int>(ProgramType::DeferredPBR)] = pbr;
	program_table_[static_cast<int>(ProgramType::DeferredPBRPost)] = pbrpost;
	program_table_[static_cast<int>(ProgramType::Shadow)] = shadow;

	StdProgram::monitor(program_table_[static_cast<int>(ProgramType::DeferredPBR)]);
	StdProgram::monitor(program_table_[static_cast<int>(ProgramType::DeferredPBRPost)]);
	StdProgram::monitor(program_table_[static_cast<int>(ProgramType::Shadow)]);
	CSProgram::monitor(post_cs0_);
	stateset_ = std::make_shared<StateSet>("std");

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void staywalk::DeferredRenderer::render_screen(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (screen_draw_program_ == kGlSickId || screen_vao_ == kGlSickId)
		init_screen_source();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, post_front_->get_color());

	GLint tex_slot = glGetUniformLocation(screen_draw_program_, "tex");
	glUniform1i(tex_slot, 0);
	glUseProgram(screen_draw_program_);
	glBindVertexArray(screen_vao_); 
	glDrawArrays(GL_TRIANGLES, 0, 3);
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

void DeferredRenderer::render(double delta, unsigned long long count){
	auto engine = Engine::get_engine();
	auto world = engine->get_world();
	if (world == nullptr) return;
	view_size_ = engine->get_view_size();
	if (view_size_.x <= 0 || view_size_.y <= 0) return;

	post_front_->resize(view_size_.x, view_size_.y);
	post_back_->resize(view_size_.x, view_size_.y);
	mainpass_gbuffer_->resize(view_size_.x, view_size_.y);

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
	StdProgram::monitor(program_table_[static_cast<int>(ProgramType::DeferredPBR)], false);
	StdProgram::monitor(program_table_[static_cast<int>(ProgramType::DeferredPBRPost)], false);
	StdProgram::monitor(program_table_[static_cast<int>(ProgramType::Shadow)], false);
	for (int i = 0; i < (int)ProgramType::_Count; i++)
		program_table_[i] = nullptr;
}

void staywalk::DeferredRenderer::render_main(){
	auto engine = Engine::get_engine();
	auto world = engine->get_world();
	
	// gbuffer pass
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mainpass_gbuffer_->get_updated_glid());
		glViewport(0, 0, engine->get_view_size().x, engine->get_view_size().y);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Tex2DRTRef shadow_tex = 0;
		RenderInfo render_info;
		{
			render_info.model_.push(mat4(1.0));
			render_info.view_.push(mat4(1.0));
			render_info.projection_.push(mat4(1.0));
		}

		if (auto cam = world->get_activated_camera()) {
			render_info.view_.top() = cam->view_;
			render_info.projection_.top() = cam->projection_;
		}
		render_info.program_ = program_table_[(int)ProgramType::DeferredPBR];

		render_info.stateset_ = stateset_;
		//render_info.stateset_->add_uniform("u_light", std::make_shared<Uniform>(light_vec));
		//render_info.stateset_->add_uniform("u_light_view_project", std::make_shared<Uniform>(light_view_project));
		//render_info.stateset_->add_tex("shadow", shadow_tex);
		render_all_mesh(render_info);
	}

	// light pass
	{
		post_front_->bind();
		if (screen_vao_ == kGlSickId) init_screen_source();
		auto program = program_table_[(int)ProgramType::DeferredPBRPost];
		program->use();

		int activated_idx = 0;
		glActiveTexture(GL_TEXTURE0 + activated_idx);
		glBindTexture(GL_TEXTURE_2D, mainpass_gbuffer_->get_albedo());
		program->set_uniform("albedo", activated_idx);
		
		activated_idx++;
		//glActiveTexture(GL_TEXTURE0 + activated_idx);
		//activated_idx++;
		//glBindTexture(GL_TEXTURE_2D, mainpass_gbuffer_->get_albedo());

		//glActiveTexture(GL_TEXTURE0 + activated_idx);
		//activated_idx++;
		//glBindTexture(GL_TEXTURE_2D, mainpass_gbuffer_->get_albedo());
		glBindVertexArray(screen_vao_);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void staywalk::DeferredRenderer::render_post0(){
	glBindFramebuffer(GL_FRAMEBUFFER, post_back_->get_updated_glid());
	glViewport(0, 0, view_size_.x, view_size_.y);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLCheck(;);
	glBindImageTexture(0, post_front_->get_color(), 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
	glBindImageTexture(1, post_back_->get_color(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	GLCheck(;);

	ivec3 work_group = ivec3(
		(view_size_.x / 256) + ((view_size_.x % 256 == 0) ? 0 : 1), 
		view_size_.y,
		1
	);

	post_cs0_->set_work_group_size(work_group);
	post_cs0_->dispatch();
	std::swap(post_front_, post_back_);
}

void staywalk::DeferredRenderer::render_post1()
{
}

void staywalk::DeferredRenderer::init_screen_source() {
	{
		glGenVertexArrays(1, &screen_vao_);
		glBindVertexArray(screen_vao_);

		vector<float> vertices{
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,		// left  
			3.0f, -1.0f, 0.0f, 2.0f, 0.0f,		// right 
			-1.0f, 3.0f, 0.0f, 0.0f, 2.0f		// top   
		};

		auto size_byte = vertices.size() * sizeof(decltype(vertices)::value_type);

		uint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size_byte, vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1); // texcoords

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	{
		string vert_code = R"(
			#version 330 core
			layout (location = 0) in vec3 vs_pos;
			layout (location = 1) in vec2 vs_texcoord;
			
			out vec2 fs_texcoord;	
			void main(){
				fs_texcoord = vs_texcoord;
			   gl_Position = vec4(vs_pos, 1.0f);
			};
		)";

		string frag_code = R"(
			#version 330 core
			uniform sampler2D tex;
			in vec2 fs_texcoord;	
            out vec4 FragColor;
			
			void main(){
			   FragColor = vec4(texture(tex, fs_texcoord).xyz, 1.0f);
			};
		)";
		auto fscode_c_str = frag_code.c_str();
		auto vscode_c_str = vert_code.c_str();

		uint vert = glCreateShader(GL_VERTEX_SHADER);
		uint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fscode_c_str, NULL);
		glShaderSource(vert, 1, &vscode_c_str, NULL);
		glCompileShader(fragment);
		glCompileShader(vert);
		screen_draw_program_ = glCreateProgram();
		glAttachShader(screen_draw_program_, fragment);
		glAttachShader(screen_draw_program_, vert);
		glLinkProgram(screen_draw_program_);

		int success;
		char infoLog[2048];
		glGetProgramiv(screen_draw_program_, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(screen_draw_program_, 2048, NULL, infoLog);
			assert(false);
		}

		glDeleteShader(fragment);
		glDeleteShader(vert);
	}
}
