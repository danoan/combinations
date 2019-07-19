cmake_minimum_required(VERSION 3.2)
project(example-multithread)

add_executable(example-multithread example-multithread.cpp)

add_dependencies(example-multithread comb-utils comb-logger)

target_include_directories(example-multithread PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(example-multithread
        -lcomb-logger
        -lcomb-utils
        -lpthread
        -lboost_system
        -lboost_filesystem)
