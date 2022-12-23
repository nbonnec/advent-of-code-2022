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

FetchContent_Declare(
        magiclib
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG v0.8.2)
FetchContent_MakeAvailable(magiclib)

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
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/9)
