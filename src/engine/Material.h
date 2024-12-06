#pragma once
#include "Common.h"
#include "RProgram.h"

#include <map>


namespace staywalk {
	class sw_Class(jsonpost;)  Material : public Object{
	public:
		static const string DiffuseKey;
		static const string AoKey;

	public:
		sw_Func()  Material(const string& name="0-material");

		~Material();

		sw_Func()  void add_tex(const string & name, RTexRef tex);
		sw_Func()  void add_uniform(const string & name, UniformRef uniform);

		sw_Prop() RProgramRef program;

		/**
		* @ same effect
		*/
		sw_Func() bool is_same(MaterialRef rhs);

		void use(RenderInfo info);

		void load_post() { if (program) RProgram::monitor(program, true); }
		void dump_post() const {}

	protected:
		sw_Prop() vector<pair<string, UniformRef>> uniforms_;
		sw_Prop() vector<pair<string, RTexRef>> texs_;
		sw_Prop() vector<int> vecce;

		MetaRegister(Material);
	};
}


