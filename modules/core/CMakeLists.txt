cmake_minimum_required(VERSION 3.2)
project(core)

add_library(core INTERFACE)
target_include_directories(core INTERFACE
        include)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

