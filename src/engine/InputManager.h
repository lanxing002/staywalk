#pragma once
#include "Input.h"


namespace staywalk {
	class  InputManager {
	public:
		bool press(Keyboard id) const { return keyboard_.state_[(int)id]; }
		bool release(Keyboard id) const { return  !keyboard_.state_[(int)id]; }

		bool left_click()	const	{ return mouse_.state_[(int)Mouse::LEFT]; }
		bool left_relase()	const	{ return !mouse_.state_[(int)Mouse::LEFT]; }
		bool right_click()	const	{ return mouse_.state_[(int)Mouse::RIGHT]; }
		bool right_relase() const	{ return !mouse_.state_[(int)Mouse::RIGHT]; }
		bool middle_click() const	{ return mouse_.state_[(int)Mouse::MIDDLE]; }
		bool middle_relase() const	{ return !mouse_.state_[(int)Mouse::MIDDLE]; }


		vec2 pos() const { return mouse_.pos_; }
		vec2 mouse_offset() const { return mouse_.mouse_offset_; }
		int wheel() const { return  (int)mouse_.wheel_offset_[1]; }

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