add_executable(example-single
        example-single.cpp)

target_compile_features(example-single PRIVATE cxx_variadic_templates)

target_include_directories(example-single PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/logger/include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(example-single
        -lcomb-utils
        -lcomb-logger
        -lboost_system
        -lboost_filesystem)

install(TARGETS example-single
        DESTINATION ${CMAKE_INSTALL_PREFIX}/example/bin)
