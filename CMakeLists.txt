cmake_minimum_required(VERSION 3.0)

project("MESSENGER_PROTOCOL")

set(SOURCE_EXE src/main.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main ${SOURCE_EXE})
add_subdirectory(tests)

target_link_libraries(main)
