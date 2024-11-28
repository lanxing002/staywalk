#pragma once
#include "GameObject.h"
#include <array>

namespace staywalk {
	
	class sw_Class() Light : public GameObject {
	public:

		sw_Func() Light(const string& name = "light-0");

		MetaRegister(Light);
	};

	using LightRef = shared_ptr<Light>;

	
	// engine use this struct to manage light
	class Engine;
	struct RLight {
		static constexpr unsigned int kMaxLights = 20;

		struct __LightBlock{
			vec3 position;
			float intensity;
			vec3 color;
			float __padding;
		};

		struct __LightBuffer{
			int light_count;
			std::array<float, 3> __padding;
			std::array<Light, kMaxLights> light_data;
		};


		uint add_light(LightRef light);

		void remove_light(uint slot);

		void update_light(uint slot, LightRef& light);

		void sync_to_gpu();

		void organize();

		void disband();

		//uint get_bind_point();

	private:
		RLight();
		~RLight();

		bool dirty = true;
		uint ubo_ = kGlSickId;
		vector<LightRef> lights_;
		__LightBuffer light_buffer_;

		friend class Engine;
	};
}
