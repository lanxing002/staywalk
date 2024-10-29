message(--<start==config==imgui>)
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


include_external_msproject(cpythoncore "${cpython_dir_}/PCbuild/pythoncore.vcxproj")
set_target_properties(cpythoncore PROPERTIES FOLDER ${third_party_folder}/cpython)

add_library(py_empty STATIC ${cpython_dir_}/PCbuild/empty.cpp)
add_custom_command(
    TARGET py_empty POST_BUILD
    COMMAND ${cpython_dir_}/PCbuild/build.bat
)
set_target_properties(py_empty PROPERTIES FOLDER ${third_party_folder}/cpython)

message(--<end==config==imgui>)