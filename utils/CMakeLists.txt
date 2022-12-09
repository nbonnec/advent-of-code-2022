add_library(
        Utils
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ScopeTime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/misc.hpp
)

target_include_directories(
        Utils
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)