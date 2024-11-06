#pragma once
#include "Object.h"
#include "Common.h"

namespace staywalk
{
	class GameObject : public Object
	{
	public:
		GameObject(const string& name = "0-game-obj")
			:Object(name) {}

		virtual void tick(float delta) {}

		virtual ObjectType get_type_value() { return ObjectType::GameObject; }

		vec3 get_location() { return location_; }
		void set_location(vec3 v) { location_ = v; }

		vec3 get_scale() { return scale_; }
		void set_scale(vec3 v) { scale_ = v; }

		quat get_rotation() { return rotation_; }
		void set_rotation(quat v) { rotation_ = v; }

		bool operator==(const GameObject& gameobj);

		void dump(ofstream& ofs, Dumper& dumper) override;
		static shared_ptr<GameObject> load(ifstream& ifs, Loader& loader);

	protected:
		static void placement_load(shared_ptr<GameObject> obj, ifstream& ifs);
		
	private:
		vec3 location_{ 0.0f };
		vec3 scale_{ 1.0f };
		quat rotation_{.0f, .0f, .0f, 1.f};
		//mat4 trans_; // model transform matrix
	};
}


