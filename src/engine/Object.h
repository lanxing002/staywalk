#pragma once
#include "Common.h"


namespace staywalk{
	class Object {
	public:
		Object(const string& name = "0-obj");
		Object(idtype load_id, const string& name = "0-obj");
		virtual ~Object() = default;

		Object(const Object&) = delete;
		Object(Object&&) = delete;
		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;
		
		sw_Prop string name;

	protected:
		sw_Prop idtype guid_;

		MetaRegister(Object, void);
	};
}



