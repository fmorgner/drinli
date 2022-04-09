cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                    The Drinli Platform Abstraction Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(PLATFORM_SOURCES)

add_library("drinli_platform" STATIC ${PLATFORM_SOURCES})

target_include_directories("drinli_platform" PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/drinli>"
)

target_link_libraries("drinli_platform" PUBLIC
    "drinli_mcu"
    "drinli_rom"
)

target_compile_features("drinli_platform" PUBLIC
    "cxx_std_20"
)

target_compile_options("drinli_platform" PUBLIC
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("drinli_platform" PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED YES
    OUTPUT_NAME "platform"
)
