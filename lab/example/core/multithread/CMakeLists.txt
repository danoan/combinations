cmake_minimum_required(VERSION 3.2)
project(example-multithread)

add_executable(example-multithread example-multithread.cpp)

add_dependencies(example-multithread magLac-utils magLac-logger)

target_include_directories(example-multithread PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(example-multithread
        -lmagLac-logger
        -lmagLac-utils
        -lpthread
        -lboost_system
        -lboost_filesystem)


install(TARGETS example-multithread
        DESTINATION ${CMAKE_INSTALL_PREFIX}/example/bin)
