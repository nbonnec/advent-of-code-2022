cmake_minimum_required(VERSION 3.15)

project(advent2022)

set(CMAKE_CXX_STANDARD 20)

# === FetchContent ===

include(FetchContent)

FetchContent_Declare(
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmtlib)

# === FetchContent ===

add_subdirectory(utils)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/6)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/7)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/8)
