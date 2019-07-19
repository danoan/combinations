cmake_minimum_required(VERSION 3.2)
project(test-multithread)

add_executable(test-multithread test-multithread.cpp
        src/correcteness.cpp
        src/execution.cpp)

target_include_directories(test-multithread PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-multithread
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem
        -lpthread)