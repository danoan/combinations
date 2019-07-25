cmake_minimum_required(VERSION 3.2)
project(magLac-logger)

add_library(magLac-logger SHARED
        src/logger.cpp)

target_include_directories(magLac-logger PRIVATE
        include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(magLac-logger
        -lboost_system
        -lboost_filesystem)
