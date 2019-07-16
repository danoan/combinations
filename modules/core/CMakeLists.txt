cmake_minimum_required(VERSION 3.2)
project(core)

add_library(core INTERFACE)
target_include_directories(core INTERFACE
        include)

if(${BUILD_TESTS})
    add_subdirectory(lab/test)
endif()

if(${BUILD_EXAMPLES})
    add_subdirectory(lab/example)
endif()

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

