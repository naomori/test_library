cmake_minimum_required(VERSION 3.10)

project(hogelib)

set(proj_topdir ${PROJECT_SOURCE_DIR})

# Source Directory
set(src_dir ${PROJECT_SOURCE_DIR}/src CACHE FILEPATH "csomeip source directory")
add_subdirectory(src)

if (NOT without-test)
    # need to call enable_tesing() at project-root
    enable_testing()

    ## pthread, googletest-1.8.1 and jansson-2.12 must be installed.
    find_package(Threads REQUIRED)
    find_package(GTest 1.8.1 REQUIRED)
    find_package(jansson REQUIRED)

    # Test Directory
    set(test_dir ${PROJECT_SOURCE_DIR}/test
        CACHE FILEPATH "csomeip test directory")
    add_subdirectory(test)
endif()

#[[
message(STATUS "*** test: dump start cmake variables ***")
get_cmake_property(_variable_names VARIABLES)
foreach(_variable_name ${_variable_names})
    message(STATUS "${_variable_name}=${${_variable_name}}")
endforeach()
message(STATUS "*** test: dump end ***")
]]
