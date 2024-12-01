#include "RProgram.h"
#include "Utility.h"
#include "SimpleType.h"


using namespace staywalk;

RShader::RShader(const string& code_text, const string& name)
	: RObject(name) {
	code = SWCode::create_code();
	code->code = code_text;
}

RProgram::RProgram(const string& name)
	: RObject(name), vs("", "vertex"), fs("", "fragment"), gs("", "geom"), cs("", "cs") {
}

void RProgram::load_post(){
	auto p = Utility::get_shaders_dir();
	auto vs_file = p / (name + ".vs"); string vs_code;
	auto fs_file = p / (name + ".fs"); string fs_code;
	auto gs_file = p / (name + ".gs"); string gs_code;
	auto cs_file = p / (name + ".cs"); string cs_code;
	if (Utility::load_text(vs_file, vs_code)) vs.code->code = vs_code;
	if (Utility::load_text(fs_file, fs_code)) fs.code->code = fs_code;
	if (Utility::load_text(gs_file, gs_code)) gs.code->code = gs_code;
	if (Utility::load_text(cs_file, cs_code)) cs.code->code = cs_code;
}

void RProgram::dump_post() const{
	auto p = Utility::get_shaders_dir();
	auto vs_file = p / (name + ".vs"); string vs_code;
	auto fs_file = p / (name + ".fs"); string fs_code;
	auto gs_file = p / (name + ".gs"); string gs_code;
	auto cs_file = p / (name + ".cs"); string cs_code;

	Utility::dump_text(vs_file, vs_code);
	Utility::dump_text(fs_file, fs_code);
	Utility::dump_text(gs_file, gs_code);
	Utility::dump_text(cs_file, cs_code);
}

