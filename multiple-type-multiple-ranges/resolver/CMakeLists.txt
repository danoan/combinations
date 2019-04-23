cmake_minimum_required(VERSION 3.2)
project(multiple-ranges-general)

add_executable(test-range test-range.cpp)

target_compile_features(test-range PRIVATE cxx_variadic_templates)

target_include_directories(test-range PRIVATE
include)





add_executable(test-single test-single.cpp src/utils.cpp)

target_compile_features(test-single PRIVATE cxx_variadic_templates)

target_include_directories(test-single PRIVATE
include)



add_executable(test-multiple-resolver test-multiple-resolver.cpp src/utils.cpp)

target_compile_features(test-multiple-resolver PRIVATE cxx_variadic_templates)

target_include_directories(test-multiple-resolver PRIVATE
include)




add_executable(test-multiple-combinator test-multiple-combinator.cpp src/utils.cpp)

target_compile_features(test-multiple-combinator PRIVATE cxx_variadic_templates)

target_include_directories(test-multiple-combinator PRIVATE
include)



add_executable(test-fundamental-combinator test-fundamental-combinator.cpp src/utils.cpp)

target_compile_features(test-fundamental-combinator PRIVATE cxx_variadic_templates)

target_include_directories(test-fundamental-combinator PRIVATE
        include)




add_executable(test-large-charge test-large-charge.cpp src/utils.cpp)

target_compile_features(test-large-charge PRIVATE cxx_variadic_templates)

target_include_directories(test-large-charge PRIVATE
        include)