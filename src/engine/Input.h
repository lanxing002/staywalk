#pragma once
#include "Common.h"

namespace staywalk{
	enum class InputDeviceType : int {
		KEYBOARD,
		MOUSE,
	};

	enum class Mouse : int{
		LEFT,
		RIGHT,
		MIDDLE,
	};

	enum class Keyboard : int {
		TAB,
		ENTER,
		ESCAPE,
		SPACE,
		BACKSPACE,

		/* num pad */
		NUM_LOCK,
		NUMPAD_ENTER,
		NUMPAD_DELETE,
		NUMPAD_MULTIPLY,
		NUMPAD_ADD,
		NUMPAD_SUBTRACT,
		NUMPAD_DIVIDE,
		NUMPAD_0,
		NUMPAD_1,
		NUMPAD_2,
		NUMPAD_3,
		NUMPAD_4,
		NUMPAD_5,
		NUMPAD_6,
		NUMPAD_7,
		NUMPAD_8,
		NUMPAD_9,

		/* Function keys */
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		/* Other keys */
		HOME,
		LEFT,
		UP,
		RIGHT,
		DOWN,
		PAGE_UP,
		PAGE_DOWN,
		INS,
		DEL,
		END,

		/* Modifier keys */
		CTRL_LEFT,
		CTRL_RIGHT,
		SHIFT_LEFT,
		SHIFT_RIGHT,
		CAPS_LOCK,
		ALT_LEFT,
		ALT_RIGHT,
		SUPER_LEFT,
		SUPER_RIGHT,

		NUMBER_0,
		NUMBER_1,
		NUMBER_2,
		NUMBER_3,
		NUMBER_4,
		NUMBER_5,
		NUMBER_6,
		NUMBER_7,
		NUMBER_8,
		NUMBER_9,

		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		COUNT
	};

	enum class EventType : int {
		Key,		// key press release
		Mouse,		// mouse click
		Move,		// mouse move
		Scroll,		// wheel scroll
	};
};

namespace staywalk {
	struct InputEvent
	{
		EventType etype;

		Keyboard keyboard;
		Mouse mouse;

		uint8_t click;

		glm::vec2 pos;
	};

	class InputManager;
	class MouseDevice {
	private:
		MouseDevice() {}
		void clear();
		bool state_[3][2];
		vec2 pos = vec2(0, 0);
		vec2 mouse_offset = vec2(.0, .0);
		vec2 wheel_offset = vec2(.0, .0);
		friend class InputManager;
	};

	class KeyBoardDevice {
	private:
		KeyBoardDevice() {}
		void clear();
		bool state_[(int)Keyboard::COUNT][2];
		friend class InputManager;
	};
}