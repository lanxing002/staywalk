#pragma once
#include "Common.h"

namespace staywalk{
	class sw_Class()  Object {
	public:
		sw_Func() Object(const string& name = "0-obj");
		Object(idtype load_id, const string& name = "0-obj");
		virtual ~Object() = default;

		Object(const Object&);
		Object(Object&&);
		Object& operator=(const Object&);
		Object& operator=(Object&&);
		
		sw_Func(nopy;)  idtype get_guid() { return guid_; }

		void construct_ui(bool can_modify);

		sw_Prop() string name_;

	protected:
		sw_Prop(nogui) idtype guid_;

		__MetaRegisterBase(Object);
	};
}



