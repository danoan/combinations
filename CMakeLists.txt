cmake_minimum_required(VERSION 3.2)
project(combinations)

link_directories(${BOOST_LIBS_DIR})

link_directories(${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/logger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")


add_subdirectory(modules/utils)
add_subdirectory(modules/logger)
add_subdirectory(modules/single-range/eager-recursive)
add_subdirectory(modules/single-range/lazy-recursive)
add_subdirectory(modules/single-range/lazy-nonrecursive)

add_subdirectory(modules/core)

add_subdirectory(app/stsr/eager-recursive)
add_subdirectory(app/stsr/lazy-recursive)
add_subdirectory(app/stsr/lazy-nonrecursive)