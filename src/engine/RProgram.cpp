#include "RProgram.h"
#include "Utility.h"
#include "Engine.h"
#include "SimpleType.h"

#include "rhi.h"


using namespace staywalk;

Shader::Shader(const string& code_text, const string& name)
	: RObject(name) {
	code_ = SWCode::create_code();
	code_->text_ = code_text;
}

void staywalk::Shader::gl_update(){
	if (shadertype_ == ShaderType::None) {
		log(fmt::format("RShader::organize --> shader {} has None shadetype", name_), LogLevel::Warn);
		return;
	}
	if (glid_ == kGlSickId || obj_shadertype_ != shadertype_) {
		glid_ = glCreateShader((GLenum)shadertype_);
		obj_shadertype_ = shadertype_;
	}
	auto source = glsl_code_.c_str();
	glShaderSource(glid_, 1, &source, NULL);
	glCompileShader(glid_);
	check_compile_error();
}

void staywalk::Shader::gl_delete(){
	if(kGlSickId != glid_)
		glDeleteShader(glid_);
	obj_shadertype_ = ShaderType::None;
}

GLuint staywalk::Shader::get_updated_glid(){
	if (dirty_) {
		gl_update();  // only compile once for every change
		dirty_ = false;
	}
	return glid_;
}

void staywalk::Shader::check_compile_error(){
	GLint success;
	GLchar info[1024];
	glGetShaderiv(glid_, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(glid_, 1024, NULL, info);
		log(fmt::format("RShader::Compile Failed --> {}", info), LogLevel::Warn);
	}
}

Program::Program(const string& name)
	: RObject(name)
	,vs_("", "vertex")
	,fs_("", "fragment")
{
	deferred_ = false;
	vs_.shadertype_ = ShaderType::VS;
	fs_.shadertype_ = ShaderType::FS;
	dirty_ = true;
}

void Program::load_post(){
	auto p = deferred_ ? Utility::get_deferred_shaders_dir() : Utility::get_forward_shaders_dir();
	auto vs_file = p / (name_ + ".vs"); string vs_code;
	auto fs_file = p / (name_ + ".fs"); string fs_code;
	if (Utility::load_text(vs_file, vs_code)) vs_.code_->text_ = vs_code;
	if (Utility::load_text(fs_file, fs_code)) fs_.code_->text_ = fs_code;
}

void Program::dump_post() const{
	auto p = deferred_ ? Utility::get_deferred_shaders_dir() : Utility::get_forward_shaders_dir();
	auto vs_file = p / (name_ + ".vs"); string vs_code = vs_.code_->text_;
	auto fs_file = p / (name_ + ".fs"); string fs_code = fs_.code_->text_;

	Utility::dump_text(vs_file, vs_code);
	Utility::dump_text(fs_file, fs_code);
}

staywalk::Program::~Program(){
}

void staywalk::Program::gl_update(){
	glid_ = glCreateProgram();
}

void staywalk::Program::gl_delete(){
	vs_.gl_delete();
	fs_.gl_delete();
	if (kGlSickId != glid_) glDeleteProgram(glid_);
}

void staywalk::Program::use() {
	if (dirty_) {
		uniforms_.clear();
		gl_update(); 
		dirty_ = false;
	}

	if (vs_.is_dirty() || fs_.is_dirty() /*|| gs.is_dirty()*/) {
		construct_glsl_code();

		uniforms_.clear();
		glAttachShader(glid_, vs_.get_updated_glid());
		glAttachShader(glid_, fs_.get_updated_glid());
		//if (gs.is_dirty()) glAttachShader(glid, gs.get_updated_id());
		glLinkProgram(glid_);
		check_link_error();
	}

	glUseProgram(glid_);
}

GLint staywalk::Program::get_uniform(const string& name){
	auto it = uniforms_.find(name);
	if (it != uniforms_.end())
		return it->second;
	GLint target = glGetUniformLocation(glid_, name.c_str());
	uniforms_[name] = target;
	return target;
}

void staywalk::Program::set_uniform(const string& name, UniformRef uniform){
	if (uniform == nullptr) return;
	auto utype = uniform->utype_;
	void* pdata = nullptr;
	switch (utype)
	{
	case staywalk::UniformType::U1f:
		pdata = &uniform->vdata_.x;
		glUniform1f(get_uniform(name), *reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U2f:
		pdata = &uniform->vdata_.x;
		glUniform2fv(get_uniform(name), 1,  reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U3f:
		pdata = &uniform->vdata_.x;
		glUniform3fv(get_uniform(name), 1, reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U4f:
		pdata = &uniform->vdata_.x;
		glUniform4fv(get_uniform(name), 1, reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U1i:
		pdata = &uniform->idata_;
		glUniform1i(get_uniform(name), *reinterpret_cast<int*>(pdata));
		break;
	case staywalk::UniformType::U2i:
		break;
	case staywalk::UniformType::U3i:
		break;
	case staywalk::UniformType::U4i:
		break;
	case staywalk::UniformType::UMat4:
		pdata = &uniform->mdata_;
		glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, reinterpret_cast<float*>(pdata));
		break;
	default:
		break;
	}

}

GLint staywalk::Program::set_uniform_block(const string& name){
	GLuint block_idx = glGetUniformBlockIndex(glid_, name.c_str());
	GLCheck(;);
	const auto it = uniforms_block_.find(block_idx);
	if (it != uniforms_block_.end()) {
		glUniformBlockBinding(glid_, it->first, it->second);
		GLCheck(;);

		return it->second;
	}
	auto bind_idx = (int)uniforms_block_.size();
	glUniformBlockBinding(glid_, block_idx, bind_idx);
	GLCheck(;);

	uniforms_block_[block_idx] = bind_idx;
	return bind_idx;
}

void staywalk::Program::check_link_error(){
	GLint success;
	GLchar info[2048];
	glGetProgramiv(glid_, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(glid_, 2048, NULL, info);
		log(fmt::format("RProgram::Link {}: Failed --> {}", name_, info), LogLevel::Warn);
	}
}

void staywalk::Program::monitor(ProgramRef program, bool flag /*= true*/){
	if (program == nullptr) return;
	auto p = program->deferred_ ? Utility::get_deferred_shaders_dir() : Utility::get_forward_shaders_dir();
	auto name = program->name_;
	auto vs_file = p / (name + ".vs"); string vs_code;
	auto fs_file = p / (name + ".fs"); string fs_code;
	auto cs_file = p / (name + ".cs"); string cs_code;
	auto weak_ref = std::weak_ptr<Program>(program);
	auto engine = Engine::get_engine();

	if (flag) {
		engine->monitor_file(FileMonitor::make_key(program->vs_.get_guid(), vs_file), [weak_ref](const string& new_context) {
			if (auto ref = weak_ref.lock()) { 
				ref->vs_.code_->text_ = new_context;
				ref->vs_.mark_dirty();
				log(fmt::format("vs::hotload {} --> suceess", ref->name_));
			}
		});
		engine->monitor_file(FileMonitor::make_key(program->fs_.get_guid(), fs_file), [weak_ref](const string& new_context) {
			if (auto ref = weak_ref.lock()) { 
				ref->fs_.code_->text_ = new_context; 
				ref->fs_.mark_dirty();
				log(fmt::format("fs::hotload {} --> suceess", ref->name_));
			}
		});
	}
	else {
		engine->cancel_monitor_file(FileMonitor::make_key(program->vs_.get_guid(), vs_file ));
		engine->cancel_monitor_file(FileMonitor::make_key( program->fs_.get_guid(), fs_file ));
	}

}

void staywalk::Program::construct_glsl_code() {
	if (!deferred_) {
		if(vs_.is_dirty()) vs_.glsl_code_ = vs_.code_->text_;
		if(fs_.is_dirty()) fs_.glsl_code_ = fs_.code_->text_;
	}
	else {
		if (vs_.is_dirty()) {
			vs_.glsl_code_ = Utility::get_deferred_vs_tempalte() + vs_.code_->text_;
		}

		if (fs_.is_dirty()) {
			fs_.glsl_code_ = Utility::get_deferred_fs_template() + fs_.code_->text_;
		}
	}
}

