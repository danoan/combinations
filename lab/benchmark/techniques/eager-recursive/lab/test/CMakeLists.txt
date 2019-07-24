cmake_minimum_required(VERSION 3.2)
project(test-eager-recursive)

add_executable(test-eager-recursive
        src/correcteness.cpp
        src/execution.cpp
        test-eager-recursive.cpp)

add_dependencies(test-eager-recursive magLac-utils magLac-logger)

target_include_directories(test-eager-recursive PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/benchmark/techniques/eager-recursive/include)

target_link_libraries(test-eager-recursive
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)

install(TARGETS test-eager-recursive
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test/bin)