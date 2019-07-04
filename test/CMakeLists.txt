cmake_minimum_required(VERSION 3.11)

set(spy_dir ${test_dir}/spy CACHE FILEPATH "csomeip spy directory")
add_subdirectory(spy)
set(moc_dir ${test_dir}/mock CACHE FILEPATH "csomeip mock directory")
add_subdirectory(mock)

include_directories($CACHE{src_dir} $CACHE{test_dir}
                    $CACHE{spy_dir} $CACHE{mock_dir})

#[[
message(STATUS "*** test: dump start cmake variables ***")
get_cmake_property(_variable_names VARIABLES)
foreach(_variable_name ${_variable_names})
    message(STATUS "${_variable_name}=${${_variable_name}}")
endforeach()
message(STATUS "*** test: dump end ***")
]]

set(cmake_c_warning_flags "-Wall -W -Wno-sign-compare")
set(cmake_c_warning_flags "${cmake_c_warning_flags} -Wno-unused-parameter")
set(CMAKE_C_FLAGS "-std=c11 -std=gnu99 -g3 -O0 ${cmake_c_warning_flags}")
set(test_coverage_flags "-fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS ${test_coverage_flags})

# compile test-code (Test_hoge)
file(GLOB TEST_HOGE_SOURCES Test_hoge.cpp)
add_executable(test_hoge ${TEST_HOGE_SOURCES})
target_link_libraries(test_hoge hoge
                      gtest gtest_main pthread)

add_test(NAME Test_hoge COMMAND test_hoge)
set_tests_properties(Test_hoge PROPERTIES LABELS Test_hoge)

# compile test-code (Test_hoge_spy)
file(GLOB TEST_HOGE_SPY_SOURCES Test_hoge_spy.cpp)
add_executable(test_hoge_spy ${TEST_HOGE_SPY_SOURCES})
target_link_libraries(test_hoge_spy hoge spy_hoge
                      gtest gtest_main pthread)

add_test(NAME Test_hoge_spy COMMAND test_hoge_spy)
set_tests_properties(Test_hoge_spy PROPERTIES LABELS Test_hoge_spy)
