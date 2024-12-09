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
		if (e.etype_ == EventType::Key) {
			keyboard_.state_[(int)e.keyboard_] = e.pressed_;
		}
		else if (e.etype_ == EventType::Mouse) {
			mouse_.state_[(int)e.mouse_] = e.pressed_;
		}
		else if (e.etype_ == EventType::Move) {
			mouse_.mouse_offset_ = e.pos_ - mouse_.pos_;
			mouse_.pos_ = e.pos_;
		}
		else if (e.etype_ == EventType::Scroll) {
			mouse_.wheel_offset_ = e.pos_;
		}

	}
}

