message("-- <start config cpython>--")
message("")
message("")
set(cpython_dir_ ${CMAKE_CURRENT_SOURCE_DIR}/cpython)

## wrong solution from chagpt
# include(ExternalProject)
# ExternalProject_Add(
#     cpython
#     SOURCE_DIR "${cpython_dir_}/Python"
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND "msbuild ${cpython_dir_}/PCbuild/pythoncore.vcxproj"
#     INSTALL_COMMAND ""
# )


# include_external_msproject(cpythoncore "${cpython_dir_}/PCbuild/pythoncore.vcxproj")
# set_target_properties(cpythoncore PROPERTIES FOLDER ${third_party_folder}/cpython)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo "staring runging build python......"
    COMMAND ${cpython_dir_}/PCbuild/build.bat  # 替换为你的 .bat 文件名
    COMMAND ${cpython_dir_}/PCbuild/deploy.bat  # 替换为你的 .bat 文件名
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "build python failed with exit code ${result}")
endif()

add_library(pylib INTERFACE)
target_include_directories(pylib INTERFACE "$<BUILD_INTERFACE:${cpython_dir_}/build/Include>")

find_library(pylib_obj NAMES python310 PATHS ${cpython_dir_}/PCbuild/amd64)
target_link_libraries(pylib INTERFACE ${pylib_obj})

# add_library(py_empty STATIC ${cpython_dir_}/PCbuild/empty.cpp)
# add_custom_command(
#     TARGET py_empty POST_BUILD
#     COMMAND ${cpython_dir_}/PCbuild/build.bat
#     COMMAND ${cpython_dir_}/PCbuild/deploy.bat
# )
# set_target_properties(py_empty PROPERTIES FOLDER ${third_party_folder}/cpython)
message("")
message("")
message("-- <end config cpython>--")