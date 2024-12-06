#include "RProgram.h"
#include "Utility.h"
#include "Engine.h"
#include "SimpleType.h"

#include "rhi.h"


using namespace staywalk;

RShader::RShader(const string& code_text, const string& name)
	: RObject(name) {
	code = SWCode::create_code();
	code->text = code_text;
}

void staywalk::RShader::organize(){
	if (shadertype == ShaderType::None) {
		log(fmt::format("RShader::organize --> shader {} has None shadetype", name), LogLevel::Warn);
	}
	if(glid == kGlSickId)
		glid = glCreateShader((GLenum)shadertype);
	auto source = code->text.c_str();
	glShaderSource(glid, 1, &source, NULL);
	glCompileShader(glid);
	check_compile_error();
}

void staywalk::RShader::disband(){
	if(kGlSickId != glid)
		glDeleteShader(glid);
}

GLuint staywalk::RShader::get_updated_id(){
	if (dirty_) {
		organize();  // only compile once for every change
		dirty_ = false;
	}
	return glid;
}

void staywalk::RShader::check_compile_error(){
	GLint success;
	GLchar info[1024];
	glGetShaderiv(glid, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(glid, 1024, NULL, info);
		log(fmt::format("RShader::Compile Failed --> {}", info), LogLevel::Warn);
	}
}

RProgram::RProgram(const string& name)
	: RObject(name)
	,vs("", "vertex")
	,fs("", "fragment")
	,gs("", "geom")
{
	vs.shadertype = ShaderType::VS;
	fs.shadertype = ShaderType::FS;
	gs.shadertype = ShaderType::GS;
	dirty_ = true;
}

void RProgram::load_post(){
	auto p = Utility::get_shaders_dir();
	auto vs_file = p / (name + ".vs"); string vs_code;
	auto fs_file = p / (name + ".fs"); string fs_code;
	auto gs_file = p / (name + ".gs"); string gs_code;
	if (Utility::load_text(vs_file, vs_code)) vs.code->text = vs_code;
	if (Utility::load_text(fs_file, fs_code)) fs.code->text = fs_code;
	if (Utility::load_text(gs_file, gs_code)) gs.code->text = gs_code;
}

void RProgram::dump_post() const{
	auto p = Utility::get_shaders_dir();
	auto vs_file = p / (name + ".vs"); string vs_code = vs.code->text;
	auto fs_file = p / (name + ".fs"); string fs_code = fs.code->text;
	auto gs_file = p / (name + ".gs"); string gs_code = gs.code->text;

	Utility::dump_text(vs_file, vs_code);
	Utility::dump_text(fs_file, fs_code);
	Utility::dump_text(gs_file, gs_code);
}

staywalk::RProgram::~RProgram(){
}

void staywalk::RProgram::organize(){
	glid = glCreateProgram();
}

void staywalk::RProgram::disband(){
	vs.disband();
	fs.disband();
	gs.disband();
	if (kGlSickId != glid) glDeleteProgram(glid);
}

void staywalk::RProgram::use() {
	if (dirty_) {
		uniforms_.clear();
		organize(); 
		dirty_ = false;
	}

	if (vs.is_dirty() || fs.is_dirty() /*|| gs.is_dirty()*/) {
		if (vs.is_dirty())  glAttachShader(glid, vs.get_updated_id());
		if (fs.is_dirty()) glAttachShader(glid, fs.get_updated_id());
		//if (gs.is_dirty()) glAttachShader(glid, gs.get_updated_id());
		glLinkProgram(glid);
		check_link_error();
	}

	glUseProgram(glid);
}

void staywalk::RProgram::set_uniform(const string& name, UniformRef uniform){
	if (uniform == nullptr) return;
	auto utype = uniform->utype_;
	void* pdata = &uniform->data_[0][0];
	switch (utype)
	{
	case staywalk::UniformType::U1f:
		glUniform1f(get_uniform(name), *reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U2f:
		glUniform2fv(get_uniform(name), 1,  reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U3f:
		glUniform3fv(get_uniform(name), 1, reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U4f:
		glUniform4fv(get_uniform(name), 1, reinterpret_cast<float*>(pdata));
		break;
	case staywalk::UniformType::U1i:
		glUniform1i(get_uniform(name), *reinterpret_cast<int*>(pdata));
		break;
	case staywalk::UniformType::U2i:
		break;
	case staywalk::UniformType::U3i:
		break;
	case staywalk::UniformType::U4i:
		break;
	case staywalk::UniformType::UMat4:
		glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, reinterpret_cast<float*>(pdata));
		break;
	default:
		break;
	}

}

void staywalk::RProgram::check_link_error(){
	GLint success;
	GLchar info[1024];
	glGetProgramiv(glid, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(glid, 1024, NULL, info);
		log(fmt::format("RProgram::Link {}: Failed --> {}", name, info), LogLevel::Warn);
	}
}

void staywalk::RProgram::monitor(RProgramRef program, bool flag /*= true*/){
	if (program == nullptr) return;
	auto p = Utility::get_shaders_dir();
	auto name = program->name;
	auto vs_file = p / (name + ".vs"); string vs_code;
	auto fs_file = p / (name + ".fs"); string fs_code;
	auto gs_file = p / (name + ".gs"); string gs_code;
	auto cs_file = p / (name + ".cs"); string cs_code;
	auto weak_ref = std::weak_ptr<RProgram>(program);
	auto engine = Engine::get_engine();

	if (flag) {
		engine->monitor_file({ program->vs.get_guid(), vs_file }, [weak_ref](const string& new_context) {
			if (auto ref = weak_ref.lock()) { 
				ref->vs.code->text = new_context;
				ref->vs.mark_dirty();
				log(fmt::format("vs::hotload {} --> suceess", ref->name));
			}
		});
		engine->monitor_file({ program->fs.get_guid(), fs_file }, [weak_ref](const string& new_context) {
			if (auto ref = weak_ref.lock()) { 
				ref->fs.code->text = new_context; 
				ref->fs.mark_dirty();
				log(fmt::format("fs::hotload {} --> suceess", ref->name));
			}
		});
		engine->monitor_file({ program->gs.get_guid(), gs_file }, [weak_ref](const string& new_context) {
			if (auto ref = weak_ref.lock()) { 
				ref->gs.code->text = new_context; 
				ref->gs.mark_dirty();
				log(fmt::format("gs::hotload {} --> suceess", ref->name));
			}
		});
	}
	else {
		engine->cancel_monitor_file({ program->vs.get_guid(), vs_file });
		engine->cancel_monitor_file({ program->fs.get_guid(), fs_file });
		engine->cancel_monitor_file({ program->gs.get_guid(), gs_file });
	}

}

