#[============================================================================[
                                    Drinli
#]============================================================================]

cmake_minimum_required(VERSION "3.21.0")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Toolchains/arm-none-eabi-gcc.cmake")

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Configuration"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
)

#[=====[ Basic Project Information ]=====]

project("Drinli"
    LANGUAGES CXX
    VERSION "1.0.0"
    DESCRIPTION "An experiment in building a bare-metal firmware for ARM systems"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

#[=====[ Basic Project Configuration ]=====]

include("LinkerScript")
include("StackSize")

option(DRINLI_PERFORM_IPO "Perform interprocedural optimization" YES)

write_linker_script()

#[=====[ Project Components ]=====]

add_subdirectory("source/rom")
add_subdirectory("source/bootstrap")

# #[=====[ Applications ]=====]

add_subdirectory("source/app")