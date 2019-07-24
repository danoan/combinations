add_executable(test-range
        test-range.cpp
        src/correcteness.cpp)

target_compile_features(test-range PRIVATE cxx_variadic_templates)

target_include_directories(test-range PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/lab/modules/logger/include
        ${CMAKE_SOURCE_DIR}/lab/modules/utils/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-range
        -lmagLac-logger
        -lboost_system
        -lboost_filesystem)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)

install(TARGETS test-range
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test/bin)