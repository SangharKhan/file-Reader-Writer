cmake_minimum_required(VERSION 3.20)
project(ReadWrite)
set(CMAKE_CXX_STANDARD 17)

include_directories(./include)
add_executable(ReadWrite main.cpp src/ReadWrite.cpp)

target_link_libraries(ReadWrite stdc++fs)

