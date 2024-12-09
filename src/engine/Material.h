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
		~Material();
		void use(RenderInfo info);
		void load_post() { if (program_) RProgram::monitor(program_, true); }
		void dump_post() const {}

		sw_Func()  Material(const string& name="0-material");
		sw_Func()  void add_tex(const string & name, RTexRef tex);
		sw_Func()  void add_uniform(const string & name, UniformRef uniform);
		sw_Func() bool is_same(MaterialRef rhs);

		sw_Prop() RProgramRef program_;

	protected:
		sw_Prop() vector<pair<string, UniformRef>> uniforms_;
		sw_Prop() vector<pair<string, RTexRef>> texs_;

		MetaRegister(Material);
	};
}


