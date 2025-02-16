message("-- ===== <start config cpython> ====")

set(cpython_dir_ ${CMAKE_SOURCE_DIR}/3rdparty/cpython)


include_external_msproject(cpythoncore "${cpython_dir_}/PCbuild/pythoncore.vcxproj")
set_target_properties(cpythoncore PROPERTIES FOLDER ${third_party_folder}/cpython)

if(NOT DEFINED builed_cpython)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E echo "staring runging build python......"
        COMMAND ${cpython_dir_}/PCbuild/build.bat  
        COMMAND ${cpython_dir_}/PCbuild/deploy_local.bat
        WORKING_DIRECTORY ${cpython_dir_}/PCbuild
        RESULT_VARIABLE result
    )
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "build python failed with exit code ${result}")
    endif()
    set(builed_cpython TRUE CACHE BOOL "had build cpython")
endif()



add_library(pylib SHARED IMPORTED)
set_property(TARGET pylib PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${cpython_dir_}/build/Include)
set(pybindir ${cpython_dir_}/PCbuild/amd64)
set_target_properties(pylib
	PROPERTIES
	IMPORTED_IMPLIB_DEBUG  ${cpython_dir_}/PCbuild/amd64/python310_d.lib
	IMPORTED_IMPLIB_RELEASE  ${cpython_dir_}/PCbuild/amd64/python310.lib
 	)

# add_library(pylib INTERFACE)
# find_library(pylib_compiled_d NAMES python310_d PATHS ${cpython_dir_}/PCbuild/amd64)
# find_library(pylib_compiled_r NAMES python310 PATHS ${cpython_dir_}/PCbuild/amd64)

# message(STATUS "found debug library ${pylib_obj_d}")
# message(STATUS "found release library ${pylib_obj_r}")

# target_include_directories(pylib INTERFACE "$<BUILD_INTERFACE:${cpython_dir_}/build/Include>")
# target_link_libraries ( pylib INTERFACE
# 						debug ${pylib_compiled_d}
# 						optimized ${pylib_compiled_r} )

message("-- ===== <end config cpython> ====")