#include "Input.h"

staywalk::MouseDevice::MouseDevice(){
	for (int i = 0; i < 3; i++) {
		state_[i] = false;
	}
}

void staywalk::MouseDevice::clear(){
	mouse_offset_ = vec2(.0, .0);
	wheel_offset_ = vec2(.0, .0);
}

staywalk::KeyBoardDevice::KeyBoardDevice(){
	for (int i = 0; i < (int)Keyboard::COUNT; i++) {
		state_[i] = false;
	}
}
