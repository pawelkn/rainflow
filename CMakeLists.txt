cmake_minimum_required(VERSION 3.14)
project(rainflow)

include_directories(src)

add_executable(example_rainflow src/rainflow.cpp example/example_rainflow.cpp)
add_executable(test_rainflow src/rainflow.cpp test/test_rainflow.cpp)

target_link_libraries(test_rainflow gtest gtest_main pthread)