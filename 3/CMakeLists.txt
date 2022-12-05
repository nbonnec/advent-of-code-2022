add_executable(3 main.cpp)

target_include_directories(
        3
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../config/
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
