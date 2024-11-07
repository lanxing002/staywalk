#pragma once
#include "Object.h"
namespace staywalk{
	class GameComponent	: public Object{
	public:
		GameComponent(const string& name = "0-comp")
			:Object(name) {}

		ObjectType get_type_value() override { return ObjectType::GameComponent; }
		inline bool operator==(const GameComponent& rhs) {
			return Object::operator==(rhs);
		}
	};
}

