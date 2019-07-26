cmake_minimum_required(VERSION 3.2)
project(maglac-coverage)

add_executable(test-coverage test-coverage.cpp
        ${CMAKE_SOURCE_DIR}/lab/test/core/fundamental-combinator/src/execution.cpp
        ${CMAKE_SOURCE_DIR}/lab/test/core/fundamental-combinator/src/correcteness.cpp
        ${CMAKE_SOURCE_DIR}/lab/test/core/multiple-resolver/src/correcteness.cpp
        ${CMAKE_SOURCE_DIR}/lab/test/core/multithread/src/correcteness.cpp
        ${CMAKE_SOURCE_DIR}/lab/test/core/multithread/src/execution.cpp
        ${CMAKE_SOURCE_DIR}/lab/test/core/range/src/correcteness.cpp)

add_dependencies(test-coverage magLac-logger magLac-utils)

target_include_directories(test-coverage PRIVATE
        ${CMAKE_SOURCE_DIR}/lab/test/core/fundamental-combinator/include
        ${CMAKE_SOURCE_DIR}/lab/test/core/multiple-resolver/include
        ${CMAKE_SOURCE_DIR}/lab/test/core/multithread/include
        ${CMAKE_SOURCE_DIR}/lab/test/core/range/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-coverage
        -lmagLac-logger
        -lmagLac-utils
        -lpthread
        -lboost_system
        -lboost_filesystem)