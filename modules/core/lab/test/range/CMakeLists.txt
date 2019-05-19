add_executable(test-range
        test-range.cpp)

target_compile_features(test-range PRIVATE cxx_variadic_templates)

target_include_directories(test-range PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include)