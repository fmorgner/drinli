cmake_minimum_required(VERSION "3.21.0")

#[============================================================================[
                                    Drinli
#]============================================================================]

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Configuration"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
)

include("CMakePackageConfigHelpers")

#[=====[ Basic Project Information ]=====]

project("Drinli"
    LANGUAGES CXX
    VERSION "1.0.0"
    DESCRIPTION "An experiment in building a bare-metal firmware for ARM systems"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

#[=====[ Conan Dependencies ]=====]

include("${PROJECT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(NO_OUTPUT_DIRS)

#[=====[ Basic Project Configuration ]=====]

include("StackSize")
include("LinkerScripts")
include("ShowConfiguration")

option(DRINLI_PERFORM_IPO "Perform interprocedural optimization" YES)

drinli_show_configuration()

#[=====[ Project Components ]=====]

add_subdirectory("source/mcu")
add_subdirectory("source/rom")
add_subdirectory("source/bootstrap")

#[=====[ Applications ]=====]

add_subdirectory("source/app")

#[=====[ Installation Configuration ]=====]

install(DIRECTORY "${PROJECT_BINARY_DIR}/scripts"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
