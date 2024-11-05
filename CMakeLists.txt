cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0)

project(staywalk)

set(CMAKE_CXX_STANDARD 17) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(3rdparty)

set(engine_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
add_executable(engine ${engine_src_dir}/main.cpp)
set_target_properties(engine PROPERTIES FOLDER staywalk/engine)
target_link_libraries(engine PRIVATE glfw glm imgui pybind11_headers fmt assimp)
target_link_libraries(engine PRIVATE glad stbimage)
target_link_libraries(engine INTERFACE stbimage)

target_include_directories(engine PRIVATE ${engine_src_dir})
set_target_properties(engine PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

file(GLOB SRC_FILES "${engine_src_dir}/*.cpp" "${engine_src_dir}/*.h")
target_sources(engine PRIVATE ${SRC_FILES})


