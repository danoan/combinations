add_executable(test-fundamental-combinator
        test-fundamental-combinator.cpp)

target_compile_features(test-fundamental-combinator PRIVATE cxx_variadic_templates)

target_include_directories(test-fundamental-combinator PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(test-fundamental-combinator
        -lcomb-utils)
