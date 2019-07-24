cmake_minimum_required(VERSION 3.2)
project(test-multithread)

add_executable(test-multithread test-multithread.cpp
        src/correcteness.cpp
        src/execution.cpp)

add_dependencies(test-multithread magLac-utils magLac-logger)

target_include_directories(test-multithread PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-multithread
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem
        -lpthread)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)

install(TARGETS test-multithread
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test/bin)