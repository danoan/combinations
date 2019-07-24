cmake_minimum_required(VERSION 3.2)
project(example-single)

add_executable(example-single
        example-single.cpp)

add_dependencies(example-single magLac-utils magLac-logger)

target_compile_features(example-single PRIVATE cxx_variadic_templates)

target_include_directories(example-single PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(example-single
        -lmagLac-utils
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)

install(TARGETS example-single
        DESTINATION ${CMAKE_INSTALL_PREFIX}/example/bin)
