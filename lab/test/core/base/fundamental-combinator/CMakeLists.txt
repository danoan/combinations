cmake_minimum_required(VERSION 3.2)
project(test-fundamental-combinator)

add_executable(test-fundamental-combinator
        test-fundamental-combinator.cpp
        src/correcteness.cpp
        src/execution.cpp)

add_dependencies(test-fundamental-combinator magLac-utils magLac-logger)

target_compile_features(test-fundamental-combinator PRIVATE cxx_variadic_templates)

target_include_directories(test-fundamental-combinator PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include)

target_link_libraries(test-fundamental-combinator
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)

