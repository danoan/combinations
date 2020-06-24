cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:${BOOST_LIBS_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

project(magLac)

link_directories(${BOOST_LIBS_DIR})

link_directories(${CMAKE_BINARY_DIR}/lab/modules/utils
        ${CMAKE_BINARY_DIR}/lab/modules/logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    if(${COVERAGE})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    endif()
endif()

if(${BUILD_EXAMPLES})
    add_subdirectory(lab/example)
    add_subdirectory(lab/benchmark)
endif()

if(${BUILD_TESTS})
    add_subdirectory(lab/test)
endif()

add_subdirectory(lab/modules/logger)
add_subdirectory(lab/modules/utils)

add_subdirectory(lab/benchmark/techniques/eager-recursive)
add_subdirectory(lab/benchmark/techniques/lazy-recursive)
add_subdirectory(lab/benchmark/techniques/lazy-nonrecursive)

add_subdirectory(modules/core)