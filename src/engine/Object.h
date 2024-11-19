#pragma once
#include "Common.h"


namespace staywalk{
	class sw_Class()  Object {
	public:
		Object(const string& name = "0-obj");
		Object(idtype load_id, const string& name = "0-obj");
		virtual ~Object() = default;

		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;
		
		sw_Func()  idtype get_guid() { return guid_; }

		void construct_ui(bool read_only);

		sw_Prop() string name;

	protected:
		sw_Prop(nogui) idtype guid_;

		MetaRegister(Object);
	};
}



