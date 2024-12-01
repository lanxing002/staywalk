#pragma once

#include "RenderObject.h"
#include "SimpleType.h"

namespace staywalk{
	class Render;

	enum class sw_Class()  ShaderType : int {
		None,
		VS,
		FS,
		CS,
	};

	class sw_Class()  RShader : public RObject {
	public:
		RShader(const string& code_text = "", const string & name = "shader-0");
		sw_Prop() ShaderType shadertype = ShaderType::None;
		sw_Prop() SWCodeRef code;

		MetaRegister(RShader);
	};

	class sw_Class()  RUniform : public RObject {
	public:

		MetaRegister(RUniform);
	};

	class sw_Class(jsonpost;)  RProgram : public RObject {
	public:
		RProgram(const string & name = "program-0");
		sw_Prop() RShader vs;
		sw_Prop() RShader fs;
		sw_Prop() RShader gs;
		sw_Prop() RShader cs;

		MetaRegister(RProgram);

	public:
		void load_post();
		void dump_post() const;

		friend class Render;
	};
}

