#[============================================================================[
                          The Drinli Bootstrap Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(BOOTSTRAP_SOURCES)

add_library("drinli-bootstrap" STATIC ${BOOTSTRAP_SOURCES})

target_include_directories("drinli-bootstrap" PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/drinli>"
)

target_compile_features("drinli-bootstrap" PUBLIC
    "cxx_std_20"
)

target_compile_options("drinli-bootstrap" PRIVATE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("drinli-bootstrap" PROPERTIES
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED YES
    INTERPROCEDURAL_OPTIMIZATION ${DRINLI_PERFORM_IPO}
)

add_library("drinli::bootstrap" ALIAS "drinli-bootstrap")