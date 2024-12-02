#pragma once

#include "RenderObject.h"
#include "SimpleType.h"

namespace staywalk{
	class Render;

	enum class sw_Class()  ShaderType : int {
		None,
		VS = GL_VERTEX_SHADER,
		FS = GL_FRAGMENT_SHADER,
		GS = GL_GEOMETRY_SHADER,
		CS = GL_COMPUTE_SHADER,
	};

	class sw_Class()  RShader : public RObject {
	public:
		RShader(const string& code_text = "", const string & name = "shader-0");
		sw_Prop() ShaderType shadertype = ShaderType::None;
		sw_Prop() SWCodeRef code;

		void organize() override;
		void disband() override;
		GLuint get_updated_id();

		MetaRegister(RShader);

	private:
		void check_compile_error();
	};

	class sw_Class()  RUniform : public RObject {
	public:

		MetaRegister(RUniform);
	};

	class sw_Class(jsonpost;)  RProgram : public RObject {
	public:
		static void monitor(RProgramRef program, bool flag = true);

	public:
		RProgram(const string & name = "program-0");
		~RProgram() override;
		sw_Prop() RShader vs;
		sw_Prop() RShader fs;
		sw_Prop() RShader gs;

		void organize() override;
		void disband() override;
		void use();
		void mark_dirty() override { }
		bool is_dirty() override { return false; }

		GLint get_uniform(const string& name) {
			auto it = uniforms_.find(name);
			if (it != uniforms_.end())
				return it->second;
			GLint target = glGetUniformLocation(glid, name.c_str());
			uniforms_[name] = target;
			return target;
		}

		template<typename T>
		void set_uniform(const string& name, T value) { static_assert(false && "not impl!!"); }
		void check_link_error();


		void load_post();
		void dump_post() const;

		MetaRegister(RProgram);

	private:
		map<string, GLint> uniforms_;
		friend class Render;
	};
}


namespace staywalk {
	template<>
	inline void RProgram::set_uniform<bool>(const string& name, bool value) {
		glUniform1i(get_uniform(name), value);
	}

	template<>
	inline void RProgram::set_uniform<int>(const string& name, int value) {
		glUniform1i(get_uniform(name), value);
	}

	template<>
	inline void RProgram::set_uniform<float>(const string& name, float value) {
		glUniform1f(get_uniform(name), value);
	}

	template<>
	inline void RProgram::set_uniform<vec2>(const string& name, vec2 value) {
		glUniform2fv(get_uniform(name), 1, &value[0]);
	}

	template<>
	inline void RProgram::set_uniform<vec3>(const string& name, vec3 value) {
		glUniform3fv(get_uniform(name), 1, &value[0]);
	}

	template<>
	inline void RProgram::set_uniform<vec4>(const string& name, vec4 value) {
		glUniform4fv(get_uniform(name), 1, &value[0]);
	}

	template<>
	inline void RProgram::set_uniform<mat4>(const string& name, mat4 value) {
		glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, &value[0][0]);
	}
}