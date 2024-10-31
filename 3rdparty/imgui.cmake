message(--<start==config==imgui>)
set(imgui_SOURCE_DIR_ ${CMAKE_SOURCE_DIR}/3rdparty/imgui)


## imgui sorce files
file(GLOB imgui_sources CONFIGURE_DEPENDS  "${imgui_SOURCE_DIR_}/*.cpp")

## imgui dependence graphics-api files
file(GLOB imgui_impl CONFIGURE_DEPENDS  
"${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.cpp" 
"${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.h"
"${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.cpp" 
"${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.h" 
"${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3_loader.h")
add_library(imgui STATIC ${imgui_sources} ${imgui_impl})
target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR_}>)
target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR_}/backends>)
target_link_libraries(imgui PUBLIC glfw)

option(IMGUI_SIMPLE_EXAMPLE "Build the imgui simple example program" ON)
if (IMGUI_SIMPLE_EXAMPLE)
    add_executable(imgui-test WIN32 ${imgui_SOURCE_DIR_}/examples/example_glfw_opengl3/main.cpp)
    target_link_libraries(imgui-test PUBLIC imgui opengl3)
    
    if (MSVC)
        # Tell MSVC to use main instead of WinMain
        set_target_properties(imgui-test PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
        set_target_properties(imgui-test PROPERTIES FOLDER ${third_party_folder}/imgui)
    endif()
endif()

message(--<end==config==imgui>)


