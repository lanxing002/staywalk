cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0)

project(staywalk)

set(CMAKE_CXX_STANDARD 17) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(3rdparty)
include(3rdparty/opengl.cmake)

if(NOT TARGET opengl3)
  message(FATAL_ERROR "not fount opengl3")
endif()

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
add_executable(engine ${src_dir}/main.cpp)
set_target_properties(engine PROPERTIES FOLDER staywalk/engine)
target_link_libraries(engine PRIVATE glfw glm imgui pybind11_headers fmt)
target_link_libraries(engine INTERFACE opengl3 pylib)


