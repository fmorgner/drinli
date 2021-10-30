#[============================================================================[
                        The Drinli On-Chip ROM Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(ROM_SOURCES)

add_library("rom" INTERFACE ${ROM_SOURCES})

target_include_directories("rom" INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/drinli>"
)

target_link_libraries("rom" INTERFACE
    "mcu"
)

target_compile_features("rom" INTERFACE
    "cxx_std_20"
)

target_compile_options("rom" INTERFACE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("rom" PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED YES
)

#[=====[ Installation Configuration ]=====]

install(TARGETS "rom"
    EXPORT "${PROJECT_NAME}Targets"
    DESTINATION "lib/drinli"
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "include/drinli"
)