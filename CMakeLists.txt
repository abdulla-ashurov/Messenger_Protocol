cmake_minimum_required(VERSION 3.0)

project(TESTS)

set(SOURCE_EXE tests/test.cpp)
set(SOURCE_LIB tests/catch_amalgamated.cpp src/detail.cpp src/packet.cpp src/messenger.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(UNIT_TESTS_LIB STATIC ${SOURCE_LIB})
add_executable(UNIT_TESTS ${SOURCE_EXE})

target_link_libraries(UNIT_TESTS UNIT_TESTS_LIB)
