cmake_minimum_required(VERSION 3.20)

project(remulator LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.c
)

add_executable(emulator ${SOURCES})

target_include_directories(emulator PRIVATE
    include
)

target_compile_options(emulator PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E rm -f
        "${CMAKE_SOURCE_DIR}/compile_commands.json"
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_BINARY_DIR}/compile_commands.json"
        "${CMAKE_SOURCE_DIR}/compile_commands.json"
)