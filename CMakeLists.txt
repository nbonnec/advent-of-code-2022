cmake_minimum_required(VERSION 3.15)

project(advent2022)

set(CMAKE_CXX_STANDARD 20)

# === FetchContent ===

include(FetchContent)

FetchContent_Declare(
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.1.1)
FetchContent_MakeAvailable(fmtlib)

FetchContent_Declare(
        magiclib
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG v0.8.2)
FetchContent_MakeAvailable(magiclib)

# === FetchContent ===

add_subdirectory(utils)

# 2022
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/3)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/6)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/7)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/8)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2022/9)

# 2023
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2023/1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2023/2)
