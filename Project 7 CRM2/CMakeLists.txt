cmake_minimum_required(VERSION 3.8)
project(Project_7_CRM2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Customer.h
        CustomerDB.cpp
        CustomerDB.h
        main.cpp
        Project7.cpp
        String.h)

add_executable(Project_7_CRM2 ${SOURCE_FILES})