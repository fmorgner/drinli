cmake_minimum_required(VERSION "3.21.0")

#[============================================================================[
                                    Drinli
#]============================================================================]

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Drinli: No toolchain defined. Falling back to default!")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/Toolchains/arm-none-eabi-gcc.cmake")
endif()

project("Drinli"
    LANGUAGES CXX
    VERSION "1.0.0"
    DESCRIPTION "An experiment in building a bare-metal firmware for ARM systems"
)

#[=====[ Basic Project Configuration ]=====]

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Configuration"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#[=====[ Basic Project Configuration ]=====]

include("MCUs")
include("StackSize")
include("ConfigureLinkerScript")
include("ShowConfiguration")

option(DRINLI_PERFORM_IPO "Perform interprocedural optimization" YES)

drinli_configure_linker_script()
drinli_show_configuration()

#[=====[ Project Components ]=====]

add_subdirectory("source/mcu")
add_subdirectory("source/rom")
add_subdirectory("source/bootstrap")

#[=====[ Applications ]=====]

add_subdirectory("source/app")

#[=====[ Installation Configuration ]=====]

install(DIRECTORY "${PROJECT_BINARY_DIR}/scripts"
    DESTINATION "lib/drinli"
)

install(DIRECTORY "cmake/Modules/" "cmake/Toolchains/"
    DESTINATION "lib/cmake"
)
