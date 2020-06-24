cmake_minimum_required(VERSION 3.2)
project(example-multi-set)

add_executable(example-multi-set
        example-multi-set.cpp)

add_dependencies(example-multi-set magLac-utils magLac-logger)

target_compile_features(example-multi-set PRIVATE cxx_variadic_templates)

target_include_directories(example-multi-set PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(example-multi-set
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)
