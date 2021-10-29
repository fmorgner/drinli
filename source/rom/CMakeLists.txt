#[============================================================================[
                        The Drinli On-Chip ROM Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(ROM_SOURCES)

add_library("drinli-rom" INTERFACE ${ROM_SOURCES})

target_include_directories("drinli-rom" INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/drinli>"
)

target_compile_features("drinli-rom" INTERFACE
    "cxx_std_20"
)

target_compile_options("drinli-rom" INTERFACE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("drinli-rom" PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED YES
)

add_library("drinli::rom" ALIAS "drinli-rom")
