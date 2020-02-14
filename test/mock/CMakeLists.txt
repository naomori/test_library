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

file(GLOB MOCK_OSAL_SOURCES mock_osal.cpp)
add_library(mock_osal STATIC ${MOCK_OSAL_SOURCES})
