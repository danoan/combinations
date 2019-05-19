add_executable(test-multiple-combinator
        test-multiple-combinator.cpp)

target_compile_features(test-multiple-combinator PRIVATE cxx_variadic_templates)

target_include_directories(test-multiple-combinator PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(test-multiple-combinator
        -lcomb-utils)
