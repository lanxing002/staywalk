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

add_custom_command(
    TARGET cpythoncore POST_BUILD
    COMMAND ${CMAKE_COMMAND} cmd //C ${cpython_dir_}/PCbuild/build.bat
)

message(--<end==config==imgui>)