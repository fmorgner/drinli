cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                          The Drinli Bootstrap Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(BOOTSTRAP_SOURCES)

add_library("drinli_bootstrap" STATIC ${BOOTSTRAP_SOURCES})

target_include_directories("drinli_bootstrap" PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/drinli>"
)

target_compile_features("drinli_bootstrap" PUBLIC
    "cxx_std_20"
)

target_compile_options("drinli_bootstrap" PRIVATE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("drinli_bootstrap" PROPERTIES
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED YES
    INTERPROCEDURAL_OPTIMIZATION ${DRINLI_PERFORM_IPO}
    OUTPUT_NAME "bootstrap"
)

#[=====[ Installation Configuration ]=====]

install(TARGETS "drinli_bootstrap"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/drinli"
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/drinli"
)
