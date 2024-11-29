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

private:
	bool shold_close();
	void process_evnet();
	void poll_events() { glfwPollEvents(); }
	void swap_buffer() { glfwSwapBuffers(window_); }
	
	void render_frame();

	static Window* curr_window;
	static void handle_resize(GLFWwindow* window, int width, int height);

private:
	EditorUI editor_ui_;
	staywalk::Renderer renderer_;

	GLFWwindow* window_;
	const int width_ = 1280;
	const int height_ = 720;

	unsigned long long frame_count_;
};

