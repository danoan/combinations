cmake_minimum_required(VERSION 3.2)
project(multiple-ranges-general)

add_executable(multiple-ranges-general main.cpp
src/utils.cpp)

target_include_directories(multiple-ranges-general PRIVATE
include)



add_executable(mytest main2.cpp
src/utils.cpp)

target_include_directories(mytest PRIVATE
include)
