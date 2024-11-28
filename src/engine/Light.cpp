#include "Light.h"
#include "Utility.h"

namespace staywalk {
	Light::Light(const string& name) 
	:GameObject(name){
	}



	/****************************************/
	/****************************************/
	RLight::RLight(){
		light_buffer_.light_count = 0;
		dirty = false;
	}

	RLight::~RLight() {
		light_buffer_.light_count = 0;
		dirty = false;
	}

	staywalk::uint RLight::add_light(LightRef light){
		auto slot = (uint)lights_.size();
		lights_.push_back(light);
		dirty = true;
		return slot;
	}

	void RLight::remove_light(uint slot){

		dirty = true;
	}

	void RLight::update_light(uint slot, LightRef& light){
		if (lights_.size() < slot)
			log(fmt::format("update light failed: slot {} had not be assign", slot), LogLevel::Warn);

		dirty = true;
		lights_[slot] = light;
	}

	void RLight::sync_to_gpu(){
		if (!dirty) return;
	}

	void RLight::organize(){

	}

	void RLight::disband(){

	}

}