cmake_minimum_required(VERSION 3.2)
project(example-multiple-combinator)

add_executable(example-multiple-combinator
        example-multiple-combinator.cpp)

add_dependencies(example-multiple-combinator magLac-utils magLac-logger)

target_compile_features(example-multiple-combinator PRIVATE cxx_variadic_templates)

target_include_directories(example-multiple-combinator PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include)

target_link_libraries(example-multiple-combinator
        -lmagLac-utils)

install(TARGETS example-multiple-combinator
        DESTINATION ${CMAKE_INSTALL_PREFIX}/example/bin)
