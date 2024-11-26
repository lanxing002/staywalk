set(third_party_folder "ThirdParty")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if(NOT TARGET glad)
    include(opengl.cmake)
    add_library(glad ${CMAKE_SOURCE_DIR}/3rdparty/opengl/src/glad.c)
    target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/opengl/include)
    target_link_libraries(glad PUBLIC opengl3)
    set_target_properties(glad PROPERTIES FOLDER ${third_party_folder}/glad)
endif()

if(NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw)
    set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
    set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
endif()

if(NOT TARGET glm)
    add_subdirectory(glm)
    set_target_properties(glm PROPERTIES FOLDER ${third_party_folder}/glm)
endif()

if(NOT TARGET imgui)
    include(imgui.cmake)
    set_target_properties(imgui PROPERTIES FOLDER ${third_party_folder}/imgui)
endif()

if(NOT TARGET cpython)
    include(cpython.cmake)
endif()

if(NOT TARGET pybind11_headers)
    include(pybind11.cmake)
endif()

if(NOT TARGET stbimage)
    add_library(stbimage INTERFACE)
    target_include_directories(stbimage INTERFACE ${CMAKE_SOURCE_DIR}/3rdparty/stb)
    # set_property(TARGET stbimage PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/stb)
endif()

if(NOT TARGET assimp)
    option(ASSIMP_BUILD_TESTS "" OFF)
    option(ASSIMP_INSTALL "" OFF)
    option(ASSIMP_INJECT_DEBUG_POSTFIX "" OFF)
    add_subdirectory(assimp)
    set_target_properties(assimp PROPERTIES FOLDER ${third_party_folder}/assimp)
    set_target_properties(zlibstatic PROPERTIES FOLDER ${third_party_folder}/assimp)
    set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER ${third_party_folder}/assimp)
endif()

if(NOT TARGET irrklang)
endif()

if(NOT TARGET freetype)
    add_subdirectory(freetype)
    set_target_properties(freetype PROPERTIES FOLDER ${third_party_folder}/freetype)
endif()

if(NOT TARGET fmt)
    add_subdirectory(fmt)
    set_target_properties(fmt PROPERTIES FOLDER ${third_party_folder}/fmt)
endif()


if(NOT TARGET RapidJSON)
    add_subdirectory(rapidjson)
endif()


if(NOT TARGET eventpp)
    add_subdirectory(eventpp)
endif()
