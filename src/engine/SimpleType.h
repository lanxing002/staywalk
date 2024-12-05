#pragma once
#include "Common.h"
/**
* @those type have gui and josn code, 
*/

namespace staywalk{
	struct Transform {
		vec3 location;
		vec3 scale;
		vec3 rotation;

		bool operator==(const Transform& rhs) const {
			return location == rhs.location &&
				scale == rhs.scale &&
				rotation == rhs.rotation;
		}

		mat4 matrix() const;

		void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const;
		void load(rapidjson::Value&, staywalk::reflect::Loader&);
	};

	struct AABB {
		AABB() { min = vec3(1.0); max = vec3(-1.0); };
		AABB(const vec3& in_min, const vec3& in_max) : min(in_min), max(in_max) {}

		vec3 min;
		vec3 max;

		bool valid() const { return max.x >= min.x && max.y >= min.y && max.z >= min.z; }

		bool operator==(const AABB& rhs) const {
			return min == rhs.min && max == rhs.max;
		}

		void expand(const AABB& value) {
			if (!value.valid()) return;
			expand(value.max);
			expand(value.min);
		}

		void expand(const vec3& v) {
			if (!valid()) {
				min = v;
				max = vec3(v.x + 1e-6, v.y + 1e-6, v.z + 1e-6);
			}
			else{
				min = vec3(std::min(min.x, v.x), std::min(min.y, v.y), std::min(min.z, v.z));
				max = vec3(std::max(max.x, v.x), std::max(max.y, v.y), std::max(max.z, v.z));
			}
		}

		void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const;
		void load(rapidjson::Value&, staywalk::reflect::Loader&);
	};


	constexpr static Transform Identity = Transform{ vec3(.0), vec3(1.0), vec3(1.0) };


	enum class CodeType : int{
		Shader = 0,
		Script = 1
	};

	namespace SWCode {
		struct __SWCode {

		private:
			__SWCode() {}

		public:
			string text;
			CodeType code_type = CodeType::Shader;

			bool operator==(const __SWCode& rhs) const {
				return text == rhs.text && code_type == rhs.code_type;
			}

			void dump(rapidjson::Value&, staywalk::reflect::Dumper&) const;
			void load(rapidjson::Value&, staywalk::reflect::Loader&);

			friend Ref<__SWCode> create_code();
		};

		static Ref<__SWCode> create_code() { return std::shared_ptr<__SWCode>(new __SWCode()); }
	}
	using SWCodeRef = Ref<SWCode::__SWCode>;
}



