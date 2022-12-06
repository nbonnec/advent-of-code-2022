set(EXE x)
add_executable(${EXE} main.cpp)

target_include_directories(
        ${EXE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../config/
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
