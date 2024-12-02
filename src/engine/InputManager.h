#pragma once
#include "Input.h"

namespace staywalk {
	class sw_Class() InputManager {
		explicit InputManager();
		~InputManager();

		sw_Func() bool pressed(Keyboard id) const;
		sw_Func() bool released(Keyboard id) const;

		sw_Func() bool left_click() const;
		sw_Func() bool right_click() const;
		sw_Func() bool middle_click() const;
		//sw_Func() bool scroll() const;
		//sw_Func() bool move() const;


		sw_Func() vec2 pos() const;
		sw_Func() int wheel() const;

		void clear();
		void set_event(const InputEvent& e);

		private:
			KeyBoardDevice keyboard_;
			MouseDevice mouse_;
	};
}