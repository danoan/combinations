cmake_minimum_required(VERSION 3.2)
project(multiple-ranges-not-general)

add_executable(multiple-ranges-not-general main.cpp
        src/SingleRangeCombinator.cpp
        src/MultipleRangeCombinator.cpp
        src/CurrentCombination.cpp
        src/utils.cpp)

target_include_directories(multiple-ranges-not-general PRIVATE
        include)
