cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                     The Drinli Generic Support Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(SUPPORT_SOURCES)

add_library("drinli_support" INTERFACE ${SUPPORT_SOURCES})

target_compile_features("drinli_rom" INTERFACE
    "cxx_std_20"
)

target_include_directories("drinli_support" INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/drinli>"
)

add_library("drinli::support" ALIAS "drinli_support")