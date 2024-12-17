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

	enum class sw_Class()  UniformType : int {
			U1f,
			U2f,
			U3f,
			U4f,
			U1i,
			U2i,
			U3i,
			U4i,
			UMat4,
	};

	class sw_Class()  Shader : public RObject {
	public:
		Shader(const string& code_text = "", const string & name = "shader-0");
		sw_Prop() ShaderType shadertype_ = ShaderType::None;
		sw_Prop() SWCodeRef code_;

		GLuint get_updated_glid();
		void gl_delete();
		MetaRegister(Shader);

	private:
		void check_compile_error();
		void gl_update();

		ShaderType obj_shadertype_ = ShaderType::None;
	};

	class sw_Class()  Uniform : public Object {
	public:
		Uniform() {};
		Uniform(int v) : utype_(UniformType::U1i) { idata_ = v; }
		Uniform(float v) : utype_(UniformType::U1f) { vdata_ = vec4(v); }
		Uniform(vec2 v) : utype_(UniformType::U2f) { vdata_ = vec4(v.x, v.y, .0, .0); }
		Uniform(vec3 v) : utype_(UniformType::U3f) { vdata_ = vec4(v.x, v.y, v.z, .0); }
		Uniform(vec4 v) : utype_(UniformType::U4f) { vdata_ = v; }
		Uniform(mat4 v) : utype_(UniformType::UMat4) { mdata_ = v; }

		void update(int v) { __copyv(v, v); }
		void update(float v) { __copyv(v, v); }
		void update(vec2 v) { __copyv(v, v.x); }
		void update(vec3 v) { __copyv(v, v.x); }
		void update(vec4 v) { __copyv(v, v.x); }
		void update(mat4 v) { __copym(v, v[0][0]); }

		MetaRegister(Uniform);

	private:
		template<typename T, typename HeadT>
		inline void __copym(T v, HeadT head) { memcpy(&mdata_[0][0], &head, sizeof v); }

		template<typename T, typename HeadT>
		inline void __copyv(T v, HeadT head) { memcpy(&vdata_.x, &head, sizeof v); }

		sw_Prop(nogui;) UniformType utype_;
		sw_Prop(nogui;) mat4 mdata_;  // max storage for mat4
		sw_Prop(nogui;) vec4 vdata_;  // max storage for mat4
		sw_Prop(nogui;) int idata_;  // max storage for mat4
		friend class Program;
	};

	class sw_Class(jsonpost;)  Program : public RObject {
	public:
		static void monitor(ProgramRef program, bool flag = true);

	public:
		sw_Func() Program(const string & name = "program-0");
		~Program() override;
		sw_Prop() Shader vs_;
		sw_Prop() Shader fs_;
		sw_Prop() Shader gs_;
		MetaRegister(Program);

		void use();
		void gl_delete();

		GLint get_uniform(const string& name);
		template<typename T>
		void set_uniform(const string& name, T value) { static_assert(false && "not impl!!"); }
		void set_uniform(const string& name, UniformRef uniform);
		GLint set_uniform_block(const string& name);
		void load_post();

	private:
		void gl_update();
		void check_link_error();
		void dump_post() const;

	private:
		map<string, GLint> uniforms_;
		map<GLuint, GLint> uniforms_block_;
		friend class Render;
	};
}


namespace staywalk {
	template<>
	inline void Program::set_uniform<bool>(const string& name, bool value) {
		glUniform1i(get_uniform(name), value);
	}

	template<>
	inline void Program::set_uniform<int>(const string& name, int value) {
		glUniform1i(get_uniform(name), value);
	}

	template<>
	inline void Program::set_uniform<float>(const string& name, float value) {
		glUniform1f(get_uniform(name), value);
	}

	template<>
	inline void Program::set_uniform<vec2>(const string& name, vec2 value) {
		glUniform2fv(get_uniform(name), 1, &value[0]);
	}

	template<>
	inline void Program::set_uniform<vec3>(const string& name, vec3 value) {
		glUniform3fv(get_uniform(name), 1, &value[0]);
	}

	template<>
	inline void Program::set_uniform<vec4>(const string& name, vec4 value) {
		glUniform4fv(get_uniform(name), 1, &value[0]);
	}

	template<>
	inline void Program::set_uniform<mat4>(const string& name, mat4 value) {
		glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, &value[0][0]);
	}
}