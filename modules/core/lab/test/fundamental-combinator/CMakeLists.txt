add_executable(test-fundamental-combinator
        test-fundamental-combinator.cpp
        src/correcteness.cpp
        src/execution.cpp)

target_compile_features(test-fundamental-combinator PRIVATE cxx_variadic_templates)

target_include_directories(test-fundamental-combinator PRIVATE
        include
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(test-fundamental-combinator
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)

install(TARGETS test-fundamental-combinator
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test/bin)
