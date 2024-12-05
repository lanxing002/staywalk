#include "Window.h"
#include "Logger.h"
#include "Engine.h"
#include "InputManager.h"
#include "Event.h"
#include <iostream>

using namespace staywalk;

Window* Window::curr_window = nullptr;
InputManager* input_mgr = nullptr;


void window_size_callback(GLFWwindow* window, int width, int height) {
	if (input_mgr == nullptr) return;
	if (Window::curr_window) {
		Window::curr_window->width_ = width;
		Window::curr_window->height_ = height;
	}
	auto engine = Engine::get_engine();
	if (engine) {
		engine->set_view_size({ width, height });
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (input_mgr == nullptr) return;
	InputEvent e;
	e.etype = EventType::Key;
    switch (key)
    {
	case GLFW_KEY_A:
        e.keyboard = Keyboard::A;
        break;
	case GLFW_KEY_B:
		e.keyboard = Keyboard::B;
		break;
	case GLFW_KEY_C:
		e.keyboard = Keyboard::C;
		break;
	case GLFW_KEY_D:
		e.keyboard = Keyboard::D;
		break;
	case GLFW_KEY_E:
		e.keyboard = Keyboard::E;
		break;
	case GLFW_KEY_F:
		e.keyboard = Keyboard::F;
		break;
	case GLFW_KEY_G:
		e.keyboard = Keyboard::G;
		break;
	case GLFW_KEY_H:
		e.keyboard = Keyboard::H;
		break;
	case GLFW_KEY_I:
		e.keyboard = Keyboard::I;
		break;
	case GLFW_KEY_J:
		e.keyboard = Keyboard::J;
		break;
	case GLFW_KEY_K:
		e.keyboard = Keyboard::K;
		break;
	case GLFW_KEY_L:
		e.keyboard = Keyboard::L;
		break;
	case GLFW_KEY_M:
		e.keyboard = Keyboard::M;
		break;
	case GLFW_KEY_N:
		e.keyboard = Keyboard::N;
		break;
	case GLFW_KEY_O:
		e.keyboard = Keyboard::O;
		break;
	case GLFW_KEY_P:
		e.keyboard = Keyboard::P;
		break;
	case GLFW_KEY_Q:
		e.keyboard = Keyboard::Q;
		break;
	case GLFW_KEY_R:
		e.keyboard = Keyboard::R;
		break;
	case GLFW_KEY_S:
		e.keyboard = Keyboard::S;
		break;
	case GLFW_KEY_T:
		e.keyboard = Keyboard::T;
		break;
	case GLFW_KEY_U:
		e.keyboard = Keyboard::U;
		break;
	case GLFW_KEY_V:
		e.keyboard = Keyboard::V;
		break;
	case GLFW_KEY_W:
		e.keyboard = Keyboard::W;
		break;
	case GLFW_KEY_X:
		e.keyboard = Keyboard::X;
		break;
	case GLFW_KEY_Y:
		e.keyboard = Keyboard::Y;
		break;
	case GLFW_KEY_Z:
		e.keyboard = Keyboard::Z;
		break;
	case GLFW_KEY_TAB:
		e.keyboard = Keyboard::TAB;
		break;
	case GLFW_KEY_ENTER:
		e.keyboard = Keyboard::ENTER;
		break;
	case GLFW_KEY_SPACE:
		e.keyboard = Keyboard::SPACE;
		break;
	case GLFW_KEY_BACKSLASH:
		e.keyboard = Keyboard::BACKSPACE;
		break;

	case GLFW_KEY_F1:
		e.keyboard = Keyboard::F1;
		break;
	case GLFW_KEY_F2:
		e.keyboard = Keyboard::F2;
		break;
	case GLFW_KEY_F3:
		e.keyboard = Keyboard::F3;
		break;
	case GLFW_KEY_F4:
		e.keyboard = Keyboard::F4;
		break;
	case GLFW_KEY_F5:
		e.keyboard = Keyboard::F5;
		break;
	case GLFW_KEY_F6:
		e.keyboard = Keyboard::F6;
		break;
	case GLFW_KEY_F7:
		e.keyboard = Keyboard::F7;
		break;
	case GLFW_KEY_F8:
		e.keyboard = Keyboard::F8;
		break;
	case GLFW_KEY_F9:
		e.keyboard = Keyboard::F9;
		break;
	case GLFW_KEY_F10:
		e.keyboard = Keyboard::F10;
		break;
	case GLFW_KEY_F11:
		e.keyboard = Keyboard::F11;
		break;
	case GLFW_KEY_F12:
		e.keyboard = Keyboard::F12;
		break;
	
	case GLFW_KEY_LEFT_SHIFT:
		e.keyboard = Keyboard::SHIFT_LEFT;
		break;
	case GLFW_KEY_RIGHT_SHIFT:
		e.keyboard = Keyboard::SHIFT_RIGHT;
		break;
	case GLFW_KEY_LEFT_ALT:
		e.keyboard = Keyboard::ALT_LEFT;
		break;
	case GLFW_KEY_RIGHT_ALT:
		e.keyboard = Keyboard::ALT_RIGHT;
		break;
	case GLFW_KEY_LEFT_CONTROL:
		e.keyboard = Keyboard::CTRL_LEFT;
		break;
	case GLFW_KEY_RIGHT_CONTROL:
		e.keyboard = Keyboard::CTRL_RIGHT;
		break;
	case GLFW_KEY_HOME:
		e.keyboard = Keyboard::HOME;
		break;
	case GLFW_KEY_LEFT:
		e.keyboard = Keyboard::LEFT;
		break;
	case GLFW_KEY_RIGHT:
		e.keyboard = Keyboard::RIGHT;
		break;
	case GLFW_KEY_UP:
		e.keyboard = Keyboard::UP;
		break;
	case GLFW_KEY_DOWN:
		e.keyboard = Keyboard::DOWN;
		break;
	case GLFW_KEY_0:
		e.keyboard = Keyboard::NUMBER_0;
		break;
	case GLFW_KEY_1:
		e.keyboard = Keyboard::NUMBER_1;
		break;
	case GLFW_KEY_2:
		e.keyboard = Keyboard::NUMBER_2;
		break;
	case GLFW_KEY_3:
		e.keyboard = Keyboard::NUMBER_3;
		break;
	case GLFW_KEY_4:
		e.keyboard = Keyboard::NUMBER_4;
		break;
	case GLFW_KEY_5:
		e.keyboard = Keyboard::NUMBER_5;
		break;
	case GLFW_KEY_6:
		e.keyboard = Keyboard::NUMBER_6;
		break;
	case GLFW_KEY_7:
		e.keyboard = Keyboard::NUMBER_7;
		break;
	case GLFW_KEY_8:
		e.keyboard = Keyboard::NUMBER_8;
		break;
	case GLFW_KEY_9:
		e.keyboard = Keyboard::NUMBER_9;
		break;
    default:
		return;
        break;
    }

	switch (action)
	{
	case GLFW_PRESS:
		e.pressed = true;
		break;
	case GLFW_RELEASE:
		e.pressed = false;
		break;
	default:
		return;
		break;
	}
	input_mgr->set_event(e);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	if (input_mgr == nullptr) return;
	InputEvent e;
	e.etype = EventType::Move;
	e.pos = vec2(xpos, ypos);
	input_mgr->set_event(e);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	if (input_mgr == nullptr) return;
	InputEvent e;
	e.etype = EventType::Scroll;
	e.pos = vec2(xoffset, yoffset);
	input_mgr->set_event(e);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (input_mgr == nullptr) return;
    InputEvent e;
	e.etype = EventType::Mouse;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		e.mouse = Mouse::LEFT;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		e.mouse = Mouse::RIGHT;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		e.mouse = Mouse::MIDDLE;
		break;
	default:
		return;
	}

    switch (action)
    {
    case GLFW_PRESS:
        e.pressed = true;
		break;
    case GLFW_RELEASE:
		e.pressed = false;
		break;
    default:
        return;
    }
    input_mgr->set_event(e);
}


Window::Window(int width, int height)
	:width_(width), height_(height){
    assert(curr_window == nullptr);
    curr_window = this;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, "<S<>W>", NULL, NULL);
    if (window_ == NULL){
        log( std::string("can not create glfw window!!"), LogLevel::Error);
        glfwTerminate();
        terminate();
    }

    glfwSetKeyCallback(window_, key_callback);
    glfwSetCursorPosCallback(window_, cursor_position_callback);
    glfwSetMouseButtonCallback(window_, mouse_button_callback);
    glfwSetScrollCallback(window_, scroll_callback);

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, Window::handle_resize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        log(std::string("Failed to initialize GLAD!!"), LogLevel::Error);
        terminate();
    }

	Event::Editor_ShowHideCursor.append([this](bool show_flag) {
		if (show_flag) glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		editor_ui_.show_hide_cursor(show_flag);
	});
}

Window::~Window(){
    curr_window = nullptr;
    auto engine = Engine::get_engine();
    engine->shutdown();
    glfwTerminate();
}

void Window::run(){
    auto engine = Engine::get_engine();
	engine->set_view_size({width_, height_});
	input_mgr = engine->get_input_mgr_raw();

    editor_ui_.initialize(window_);
    engine->initialize();

    while (!shold_close()){
        frame_count_++;
        process_evnet();
        
        auto engine = Engine::get_engine();
		engine->logic_update(1.0);
		engine->render_update();
        {  // render editor ui
			editor_ui_.render();
			editor_ui_.render_post();
        }
        swap_buffer();
		engine->event_clear();
        poll_events();
    }
}

void Window::handle_resize(GLFWwindow* window, int width, int height){
}


bool Window::shold_close(){
    return glfwWindowShouldClose(window_);
}

void Window::process_evnet() {
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);
}


