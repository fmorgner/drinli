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

target_link_libraries("drinli_rom" INTERFACE
    "drinli_mcu"
)

target_compile_features("drinli_rom" INTERFACE
    "cxx_std_20"
)

target_compile_options("drinli_rom" INTERFACE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("drinli_rom" PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED YES
    OUTPUT_NAME "rom"
)

#[=====[ Installation Configuration ]=====]

install(TARGETS "drinli_rom"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/drinli"
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/drinli"
)
