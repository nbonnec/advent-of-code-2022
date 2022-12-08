add_library(
        Utils
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/TimeMeasure.cpp
)

target_include_directories(
        Utils
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)