cmake_minimum_required(VERSION 3.2)
project(test-lazy-recursive)

add_executable(test-lazy-recursive
        src/correcteness.cpp
        src/execution.cpp
        test-lazy-recursive.cpp)

add_dependencies(test-lazy-recursive magLac-utils magLac-logger)

target_include_directories(test-lazy-recursive PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/benchmark/techniques/lazy-recursive/include)

target_link_libraries(test-lazy-recursive
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)

install(TARGETS test-lazy-recursive
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test/bin)