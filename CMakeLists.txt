cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(210CTWeek1)
set(SOURCE_FILES "Week1/main.cpp")
add_executable(210CTWeek1 ${SOURCE_FILES})