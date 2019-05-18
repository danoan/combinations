cmake_minimum_required(VERSION 3.2)
project(combinations)

link_directories(${BOOST_LIBS_DIR})

link_directories(${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/logger)

add_subdirectory(modules/utils)
add_subdirectory(modules/logger)
add_subdirectory(modules/single-type-single-range/eager-recursive)

add_subdirectory(app/stsr/eager-recursive)