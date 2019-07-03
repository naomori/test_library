cmake_minimum_required(VERSION 3.11)

include_directories($CACHE{src_dir})

if (NOT without-test)
    set(cmake_c_warning_flags "-Wall -W -Wno-sign-compare")
    set(cmake_c_warning_flags "${cmake_c_warning_flags} -Wno-unused-parameter")
    set(test_coverage_flags "-fprofile-arcs -ftest-coverage")

    set(CMAKE_C_FLAGS "-std=c99 -std=c11 -std=gnu99 -g3 -O0 \
                       ${cmake_c_warning_flags} ${test_coverage_flags}")
    set(CMAKE_EXE_LINKER_FLAGS ${test_coverage_flags})
else()
    set(CMAKE_C_FLAGS "-std=c99 -std=c11 -std=gnu99 -O3 -Wall -W")
endif()

#[[
message(STATUS "*** test: dump start cmake variables ***")
get_cmake_property(_variable_names VARIABLES)
foreach(_variable_name ${_variable_names})
    message(STATUS "${_variable_name}=${${_variable_name}}")
endforeach()
message(STATUS "*** test: dump end ***")
]]

file(GLOB HOGE_SOURCES hoge.c)
add_library(hoge STATIC ${HOGE_SOURCES})

add_library(libhoge SHARED ${HOGE_SOURCES})
install(TARGETS libhoge DESTINATION lib)

add_library(libhoge-static STATIC ${HOGE_SOURCES})
install(TARGETS libhoge-static DESTINATION lib)

# install header files
file(GLOB API_HEADERS hoge.h)
install(FILES $API_HEADERS DESTINATION include)
