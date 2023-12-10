
get_filename_component(DAY ${CMAKE_CURRENT_LIST_DIR} NAME)

set(OUT "2023-${DAY}")

add_executable(${OUT} main.cpp)

target_include_directories(
        ${OUT}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../config/
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${OUT} PRIVATE Utils fmt::fmt magic_enum::magic_enum)
