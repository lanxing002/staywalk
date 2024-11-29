#pragma once
#include "Common.h"
#include "RProgram.h"

#include <map>


namespace staywalk {
	class sw_Class()  Material : public Object{
	public:
		static const string DiffuseKey;
		static const string AoKey;

	public:
		sw_Func()  Material(RShaderRef shader = nullptr, const string& name="0-material");

		sw_Func()  void add_tex(const string& name, RTexRef tex) { texs_[name] = tex; }
		sw_Func()  void add_uniform(const string& name, UniformRef uniform) { uniforms_[name] = uniform; }

		sw_Prop() RProgram program;

		/**
		* @ same effect
		*/
		sw_Func() bool is_same(MaterialRef rhs);

		void use();

	protected:
		sw_Prop() map<string, UniformRef> uniforms_;
		sw_Prop() map<string, RTexRef> texs_;

		MetaRegister(Material);
	};
}


