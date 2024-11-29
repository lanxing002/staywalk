#pragma once

#include "RenderObject.h"
#include "SimpleType.h"

namespace staywalk{
	enum class sw_Class()  ShaderType : int {
		None,
			VS,
			FS,
			CS,
	};

	class sw_Class()  RShader : public RObject {
	public:
		RShader(const string & name = "shader-0");
		sw_Prop() ShaderType shadertype = ShaderType::None;
		sw_Prop() SWCodeRef code;

		MetaRegister(RShader);
	};

	class sw_Class()  RUniform : public RObject {
	public:

		MetaRegister(RUniform);
	};

	class sw_Class()  RProgram : public RObject {
	public:
		RProgram(const string & name = "program-0");
		sw_Prop() RShader vs;
		sw_Prop() RShader fs;

		MetaRegister(RProgram);
	};
}

