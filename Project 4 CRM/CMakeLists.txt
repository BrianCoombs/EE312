cmake_minimum_required(VERSION 3.8)
project(Project_4_CRM)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.cpp MyString.h Invent.h Project4.cpp MyString.cpp cmake-build-debug/test1.txt cmake-build-debug/test2.txt cmake-build-debug/test3.txt Makefile GRADE_REPORT.txt)
add_executable(Project_4_CRM ${SOURCE_FILES})