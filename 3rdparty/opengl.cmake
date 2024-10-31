if(NOT TARGET opengl3)
set(opengl_SOURCE_DIR_ ${CMAKE_SOURCE_DIR}/3rdparty/opengl)
add_library(opengl3 STATIC IMPORTED)
# set_property(TARGET opengl3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${opengl_SOURCE_DIR_})
set_target_properties(opengl3
	PROPERTIES
	IMPORTED_LOCATION_DEBUG  ${opengl_SOURCE_DIR_}/OpenGL32.Lib
	IMPORTED_LOCATION_RELEASE  ${opengl_SOURCE_DIR_}/OpenGL32.Lib
)
endif()