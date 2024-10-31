set(third_party_folder "ThirdParty")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
include(opengl.cmake)

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
    target_include_directories(stbimage INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stb")
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

# if(NOT TARGET spdlog)
#     option(SPDLOG_BUILD_EXAMPLE "" OFF)
#     option(SPDLOG_INSTALL "" OFF)
#     add_subdirectory(spdlog)
#     set_target_properties(spdlog PROPERTIES FOLDER ${third_party_folder}/spdlog)
# endif()

# if(NOT TARGET stb)
#     include(stb.cmake)
#     set_target_properties(stb PROPERTIES FOLDER ${third_party_folder}/stb)
# endif()

# if(NOT TARGET tinyobjloader)
#     add_subdirectory(tinyobjloader)
#     set_target_properties(tinyobjloader PROPERTIES FOLDER ${third_party_folder}/tinyobjloader)
#     set_target_properties(uninstall PROPERTIES FOLDER ${third_party_folder}/tinyobjloader)
# endif()

# if(NOT TARGET Jolt)
#     option(TARGET_HELLO_WORLD "" OFF)
#     option(TARGET_PERFORMANCE_TEST "" OFF)
#     option(TARGET_SAMPLES "" OFF)
#     option(TARGET_UNIT_TESTS "" OFF)
#     option(TARGET_VIEWER "" OFF)

#     if(ENABLE_PHYSICS_DEBUG_RENDERER)
#         option(TARGET_TEST_FRAMEWORK "" ON)
#     else()
#         option(TARGET_TEST_FRAMEWORK "" OFF)
#     endif()

#     add_subdirectory(JoltPhysics/Build)

#     if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#         include(CheckCXXCompilerFlag)
#         check_cxx_compiler_flag("-Wno-unqualified-std-cast-call" COMPILER_CHECK_UNQUALIFIED)
#         if(COMPILER_CHECK_UNQUALIFIED)
#             target_compile_options(Jolt PRIVATE "-Wno-unqualified-std-cast-call")
#         endif()
#     endif()

#     if(ENABLE_PHYSICS_DEBUG_RENDERER)
#         set_target_properties(Jolt TestFramework
#             PROPERTIES 
#             FOLDER ${third_party_folder}/JoltPhysics
#             MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
#     else()
#         set_target_properties(Jolt
#             PROPERTIES 
#             FOLDER ${third_party_folder}/JoltPhysics
#             MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
#     endif()

#     if (MSVC)
#         target_compile_options(Jolt PRIVATE "/W4")
#     else()
#         target_compile_options(Jolt PRIVATE "-Wall")
#     endif()
# endif()

# if(NOT TARGET sol2)
#     add_subdirectory(sol2-3.3.0)
# endif()


# if(NOT TARGET lua)
#     include(lua.cmake)
# endif()
