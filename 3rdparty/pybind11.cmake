message("-- ===== <start config pybind11> ====")

option(PYBIND11_NOPYTHON "use project python" ON)
add_subdirectory(pybind11)
target_link_libraries(pybind11_headers INTERFACE pylib)

option(PYBIND11_SIMPLE_EXAMPLE "Build the imgui simple example program" ON)
if (PYBIND11_SIMPLE_EXAMPLE)
    set(pybind_test_dir_ ${CMAKE_CURRENT_SOURCE_DIR}/pybind11/tests/test_embed)
    add_executable(pybind11-test ${pybind_test_dir_}/test_interpreter.cpp ${pybind_test_dir_}/catch.cpp)
    target_include_directories(pybind11-test PRIVATE ${pybind_test_dir_})
    target_link_libraries(pybind11-test PRIVATE pybind11::embed)
    target_link_libraries(pybind11-test PRIVATE pybind11::module)
    target_link_libraries(pybind11-test PRIVATE pybind11::headers)
    set_target_properties(pybind11-test PROPERTIES FOLDER ${third_party_folder}/pybind11)

    set_target_properties(pybind11-test
         PROPERTIES
        VS_DEBUGGER_ENVIRONMENT "PATH=${pybindir};%PATH%"
    )
endif()

message("-- ===== <end config pybind11> ====")
