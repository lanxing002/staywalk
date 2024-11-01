#pragma once
#include "Object.h"
#include "Common.h"

namespace staywalk
{
	class GameObject : public Object
	{
	public:
		virtual void tick(float delta) = 0;

		vec3 get_location() { return location_; }
		void set_location(vec3 v) { location_ = v; }

		vec3 get_scale() { return scale_; }
		void set_scale(vec3 v) { scale_ = v; }

		quat get_rotation() { return rotation_; }
		void set_rotation(quat v) { rotation_ = v; }

	private:
		vec3 location_{ 0.0f };
		vec3 scale_{ 1.0f };
		quat rotation_{.0f, .0f, .0f, 1.f};
		mat4 trans_; // model transform matrix
	};
}


