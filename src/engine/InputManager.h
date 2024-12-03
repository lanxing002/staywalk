#pragma once
#include "Input.h"


namespace staywalk {
	class  InputManager {
	public:
		bool press(Keyboard id) const { return keyboard_.state_[(int)id][0]; }
		bool release(Keyboard id) const { return  keyboard_.state_[(int)id][1]; }

		bool left_click()	const	{ return mouse_.state_[(int)Mouse::LEFT][0]; }
		bool left_relase()	const	{ return mouse_.state_[(int)Mouse::LEFT][1]; }
		bool right_click()	const	{ return mouse_.state_[(int)Mouse::RIGHT][0]; }
		bool right_relase() const	{ return mouse_.state_[(int)Mouse::RIGHT][1]; }
		bool middle_click() const	{ return mouse_.state_[(int)Mouse::MIDDLE][0]; }
		bool middle_relase() const	{ return mouse_.state_[(int)Mouse::MIDDLE][1]; }


		vec2 pos() const { return mouse_.pos; }
		vec2 mouse_offset() const { return mouse_.mouse_offset; }
		int wheel() const { return  (int)mouse_.wheel_offset[1]; }

		void clear();
		void set_event(const InputEvent& e);

		private:
			explicit InputManager();
			~InputManager() {}

			KeyBoardDevice keyboard_;
			MouseDevice mouse_;

			friend class Engine;
	};
}