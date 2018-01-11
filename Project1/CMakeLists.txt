cmake_minimum_required(VERSION 3.8)
project(Project1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Project1.cpp)

add_executable(Project1 ${SOURCE_FILES})