#[============================================================================[
                                    Drinli
#]============================================================================]

cmake_minimum_required(VERSION "3.21.0")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Toolchains/arm-none-eabi-gcc.cmake")

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

#[=====[ Basic Project Configuration ]=====]

include("LinkerScript")
include("StackSize")

option(DRINLI_PERFORM_IPO "Perform interprocedural optimization" YES)

write_linker_script()

#[=====[ Project Components ]=====]

add_subdirectory("source/mcu")
add_subdirectory("source/rom")
add_subdirectory("source/bootstrap")

#[=====[ Applications ]=====]

add_subdirectory("source/app")

#[=====[ Installation Configuration ]=====]

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY "AnyNewerVersion"
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/cmake/Modules"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
)

install(EXPORT "${PROJECT_NAME}Targets"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
    NAMESPACE "drinli"
)