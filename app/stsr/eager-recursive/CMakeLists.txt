cmake_minimum_required(VERSION 3.2)
project(app-eager-recursive)

add_executable(app-eager-recursive eager-recursive.cpp)
add_dependencies(app-eager-recursive comb-utils)

target_include_directories(app-eager-recursive PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/single-range/eager-recursive/include)

target_link_libraries(app-eager-recursive
        -lcomb-utils)