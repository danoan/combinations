add_executable(test-multiple-resolver
        test-multiple-resolver.cpp)

target_compile_features(test-multiple-resolver PRIVATE cxx_variadic_templates)

target_include_directories(test-multiple-resolver PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include)

target_link_libraries(test-multiple-resolver
        -lcomb-utils)