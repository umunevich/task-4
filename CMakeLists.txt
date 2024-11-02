cmake_minimum_required(VERSION 3.8.0)

project(task-4)

set(CMAKE_CXX_STANDARD 20)

add_executable(task-4 main.cpp
        ConcurrentDS.h
        ConcurrentDS.cpp)