#include "Input.h"

void staywalk::MouseDevice::clear(){
	for (int i = 0; i < (int)Keyboard::COUNT; i++) {
		state_[i][0] = false;
		state_[i][1] = false;
	}

	mouse_offset = vec2(.0, .0);
	wheel_offset = vec2(.0, .0);
}

void staywalk::KeyBoardDevice::clear(){
	for (int i = 0; i < 3; i++) {
		state_[i][0] = false;
		state_[i][1] = false;
	}
}
