add_executable(test-single
        test-single.cpp)

target_compile_features(test-single PRIVATE cxx_variadic_templates)

target_include_directories(test-single PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(test-single
        -lcomb-utils)