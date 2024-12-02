#include "InputManager.h"

using namespace staywalk;

namespace staywalk {
	InputManager::InputManager() {

	}

	void InputManager::clear(){
		keyboard_.clear();
		mouse_.clear();
	}

	void InputManager::set_event(const InputEvent& e){
		if (e.device == InputDeviceType::KEYBOARD) {
			if (e.press) keyboard_.state_[(int)e.keyboard][0] = true;
			else keyboard_.state_[(int)e.keyboard][1] = true;
		}
		else if (e.device == InputDeviceType::MOUSE) {
			if (e.click == 1) mouse_.state_[(int)e.mouse][0] = true;
			if (e.click == 2) mouse_.state_[(int)e.mouse][1] = true;
			
			if (e.pos.x > 0) mouse_.pos = e.pos;
			if (e.wheel > 0) mouse_.wheel = e.wheel;
		}
	}
}

