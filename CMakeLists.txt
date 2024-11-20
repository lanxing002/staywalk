cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0)

project(staywalk)

set(CMAKE_CXX_STANDARD 17) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(3rdparty)

set(engine_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
add_executable(engine ${engine_src_dir}/main.cpp)
set_target_properties(engine PROPERTIES FOLDER staywalk)
target_link_libraries(engine PRIVATE glfw glm imgui pybind11_headers fmt assimp glad stbimage)

target_include_directories(engine PRIVATE ${engine_src_dir})
set_target_properties(engine PROPERTIES FOLDER "staywalk")

get_target_property(rapidjosn_includes RapidJSON INCLUDE_DIRECTORIES)
target_include_directories(engine PRIVATE ${rapidjosn_includes})

file(GLOB SRC_FILES "${engine_src_dir}/*.cpp" "${engine_src_dir}/*.h")
target_sources(engine PRIVATE ${SRC_FILES})
source_group("core" FILES ${SRC_FILES})

if(MSVC)
    target_compile_options(engine PRIVATE "/utf-8")
endif()

set_target_properties(engine PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

##  setup reflect  ##
set(reflect_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect)
target_include_directories(engine PRIVATE ${reflect_src_dir})

file(GLOB REFLECT_SRC_FILES "${reflect_src_dir}/*.cpp" "${reflect_src_dir}/*.h")
file(GLOB GENERATED_SRC_FILES "${reflect_src_dir}/generated/*.cpp" "${reflect_src_dir}/generated/*.h")
target_sources(engine PRIVATE ${REFLECT_SRC_FILES})
target_sources(engine PRIVATE ${GENERATED_SRC_FILES})
source_group("reflect" FILES ${REFLECT_SRC_FILES})
source_group("generated" FILES ${GENERATED_SRC_FILES})
##  end setup reflect  ##

## auto generate code ##
add_executable(generate_code ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/setup.cpp)
set_target_properties(generate_code PROPERTIES FOLDER "staywalk")

set(py_exe ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cpython/PCbuild/amd64/python.exe)
set(py_parse_code ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/script/startup.py)
add_custom_command(
    TARGET generate_code POST_BUILD  
    COMMAND cd "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/script"
    COMMAND "${py_exe}" "${py_parse_code}" "${CMAKE_CURRENT_SOURCE_DIR}/src" 
    COMMENT "Running parse reflect event"
)
## end auto generate code ##
set(editor_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/editor)
file(GLOB Editor_SRC_FILES "${editor_src_dir}/*.cpp" "${editor_src_dir}/*.h")
target_include_directories(engine PRIVATE ${editor_src_dir})
target_sources(engine PRIVATE ${Editor_SRC_FILES})
source_group("editor" FILES ${Editor_SRC_FILES})
