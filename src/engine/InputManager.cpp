#include "InputManager.h"
#include <iostream>

using namespace staywalk;

namespace staywalk {
	InputManager::InputManager() {

	}

	void InputManager::clear(){
		keyboard_.clear();
		mouse_.clear();
	}

	void InputManager::set_event(const InputEvent& e){
		if (e.etype == EventType::Key) {
			keyboard_.state_[(int)e.keyboard] = e.pressed;
		}
		else if (e.etype == EventType::Mouse) {
			mouse_.state_[(int)e.mouse] = e.pressed;
		}
		else if (e.etype == EventType::Move) {
			mouse_.mouse_offset = e.pos - mouse_.pos;
			mouse_.pos = e.pos;
		}
		else if (e.etype == EventType::Scroll) {
			mouse_.wheel_offset = e.pos;
		}

	}
}

