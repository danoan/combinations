cmake_minimum_required(VERSION 3.2)
project(magLac-test-coverage)

add_subdirectory(core/fundamental-combinator)
add_subdirectory(core/multiple-resolver)
add_subdirectory(core/range)
add_subdirectory(core/multithread)

add_executable(test-coverage test-coverage.cpp
        core/fundamental-combinator/src/execution.cpp
        core/fundamental-combinator/src/correcteness.cpp
        core/multiple-resolver/src/correcteness.cpp
        core/multithread/src/correcteness.cpp
        core/multithread/src/execution.cpp
        core/range/src/correcteness.cpp)

add_dependencies(test-coverage magLac-logger magLac-utils)

target_include_directories(test-coverage PRIVATE
        core/fundamental-combinator/include
        core/multiple-resolver/include
        core/multithread/include
        core/range/include
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