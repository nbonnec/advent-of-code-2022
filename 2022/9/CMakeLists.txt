
get_filename_component(DAY ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${DAY} main.cpp)

target_include_directories(
        ${DAY}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../config/
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${DAY} PRIVATE Utils fmt::fmt magic_enum::magic_enum)
