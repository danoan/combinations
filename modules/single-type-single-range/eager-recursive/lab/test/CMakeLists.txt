cmake_minimum_required(VERSION 3.2)
project(test-eager-recursive)

add_executable(test-eager-recursive
        src/correcteness.cpp
        src/execution.cpp
        test-eager-recursive.cpp)

add_dependencies(test-eager-recursive comb-utils comb-logger)

target_include_directories(test-eager-recursive PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${CMAKE_SOURCE_DIR}/modules/single-type-single-range/eager-recursive/include)

target_link_libraries(test-eager-recursive
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem)