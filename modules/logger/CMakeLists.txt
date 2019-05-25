cmake_minimum_required(VERSION 3.2)
project(comb-logger)

add_library(comb-logger SHARED
        src/logger.cpp)

target_include_directories(comb-logger PRIVATE
        include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(comb-logger
        -lboost_system
        -lboost_filesystem)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS comb-logger
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
