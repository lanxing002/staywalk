#pragma once
#include "Common.h"

namespace staywalk{
	class sw_Class()  Object {
	public:
		sw_Func() Object(const string& name = "0-obj");
		sw_Func()  idtype get_guid() { return guid_; }
		sw_Prop() string name_;
		__MetaRegisterBase(Object);

		Object(idtype load_id, const string& name = "0-obj");
		virtual ~Object() = default;
		Object(const Object&);
		Object(Object&&);
		Object& operator=(const Object&);
		Object& operator=(Object&&);
		void construct_ui(bool can_modify);
	

	protected:
		sw_Prop(nogui) idtype guid_;
	};
}



