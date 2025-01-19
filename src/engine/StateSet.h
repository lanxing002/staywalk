#pragma once
#include "Common.h"
#include "RProgram.h"

#include <map>


namespace staywalk {
	class sw_Class()  StateSet : public Object{
	public:
		sw_Func()  StateSet(const string& name="0-stateset");
		sw_Func()  void add_tex(const string & name, TexRef tex);
		sw_Func()  void add_uniform(const string & name, UniformRef uniform);
		sw_Func()  void remove_tex(const string & name) { texs_.erase(name); }
		sw_Func()  void remove_uniform(const string& name) { uniforms_.erase(name); }
		sw_Func() bool is_same(StateSetRef rhs);
		sw_Func() int get_tex_slot(const string& name);
		MetaRegister(StateSet);

	public:
		static const string DiffuseKey;
		static const string AoKey;

		~StateSet();
		void use(StdProgramRef program, int tex_slot_bias = 0);
		int get_texture_num() { return (int)texs_.size(); }

	protected:
		sw_Prop() map<string, UniformRef> uniforms_;
		sw_Prop() map<string, TexRef> texs_;

	private:
		map<string, int> tex_slot_;
	};
}


