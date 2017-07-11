cmake_minimum_required(VERSION 2.8)
project(saveload)

set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")

find_package(GTest REQUIRED)
link_directories(${PROJECT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(tests tests.cpp saveload.h)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)
add_test(tests tests)

