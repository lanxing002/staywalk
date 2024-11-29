#include "RProgram.h"
#include "Utility.h"

using namespace staywalk;

RShader::RShader(const string& name)
	: RObject(name) {
	code = SWCode::create_code();
}

RProgram::RProgram(const string& name)
	: RObject(name) {
}

