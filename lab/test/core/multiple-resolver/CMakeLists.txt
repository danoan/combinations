cmake_minimum_required(VERSION 3.2)
project(test-multiple-resolver)

add_executable(test-multiple-resolver
        test-multiple-resolver.cpp
        src/correcteness.cpp)

add_dependencies(test-multiple-resolver magLac-utils magLac-logger)

target_compile_features(test-multiple-resolver PRIVATE cxx_variadic_templates)

target_include_directories(test-multiple-resolver PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-multiple-resolver
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)

install(TARGETS test-multiple-resolver
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test/bin)