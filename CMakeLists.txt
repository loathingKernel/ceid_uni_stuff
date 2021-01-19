cmake_minimum_required(VERSION 3.0)

project(cpp_project)

add_executable(cpp_project main.cpp)

install(TARGETS cpp_project RUNTIME DESTINATION bin)
