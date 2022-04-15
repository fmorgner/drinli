cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                        The Drinli On-Chip ROM Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(ROM_SOURCES)

add_library("drinli_rom" INTERFACE ${ROM_SOURCES})

target_include_directories("drinli_rom" INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/drinli>"
)

target_compile_features("drinli_rom" INTERFACE
    "cxx_std_20"
)

target_link_libraries("drinli_rom" INTERFACE
    "drinli::support"
)

add_library("drinli::rom" ALIAS "drinli_rom")