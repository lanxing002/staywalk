#pragma once
#include "rhi.h"
#include "EditorUI.h"
#include "Renderer.h"

/**
*@brieft wrap of glfw window, one app one window 
*/
class Window{
public:
	Window(int width = 1280, int height = 720);
	~Window();

	void run();

	bool shold_close();
	void process_evnet();
	void poll_events() { glfwPollEvents(); }
	void swap_buffer() { glfwSwapBuffers(window_); }
	
	static Window* curr_window;
	static void handle_resize(GLFWwindow* window, int width, int height);

	EditorUI editor_ui_;
	GLFWwindow* window_;

	int width_ = 1280;
	int height_ = 720;
	unsigned long long frame_count_;
};

