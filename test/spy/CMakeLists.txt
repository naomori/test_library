cmake_minimum_required(VERSION 3.10)

include_directories($CACHE{src_dir})

#[[
message(STATUS "*** test: dump start cmake variables ***")
get_cmake_property(_variable_names VARIABLES)
foreach(_variable_name ${_variable_names})
    message(STATUS "${_variable_name}=${${_variable_name}}")
endforeach()
message(STATUS "*** test: dump end ***")
]]

file(GLOB SPY_HOGE_SOURCES spy_hoge.c)
add_library(spy_hoge STATIC ${SPY_HOGE_SOURCES})
