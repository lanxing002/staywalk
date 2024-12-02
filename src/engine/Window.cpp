#include "Window.h"
#include "Logger.h"
#include "Engine.h"

using namespace staywalk;

Window* Window::curr_window = nullptr;

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
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, Window::handle_resize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        log(std::string("Failed to initialize GLAD!!"), LogLevel::Error);
        terminate();
    }
}

Window::~Window(){
    curr_window = nullptr;
    auto engine = Engine::get_engine();
    engine->shutdown();
    glfwTerminate();
}

void Window::run(){
    auto engine = Engine::get_engine();
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


