cmake_minimum_required(VERSION 3.2)
project(example-single-set)

add_executable(example-single-set
        example-single-set.cpp)

add_dependencies(example-single-set magLac-utils magLac-logger)

target_compile_features(example-single-set PRIVATE cxx_variadic_templates)

target_include_directories(example-single-set PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(example-single-set
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)
