
cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                              The Drinli Demo App
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")
include("AddFirmware")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(APP_SOURCES)

drinli_add_firmware("app" ${APP_SOURCES})

target_include_directories("app" PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
