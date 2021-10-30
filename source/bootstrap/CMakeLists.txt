cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                          The Drinli Bootstrap Library
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("GlobComponentSources")

#[=====[ Library Target ]=====]

drinli_glob_component_sources(BOOTSTRAP_SOURCES)

add_library("bootstrap" STATIC ${BOOTSTRAP_SOURCES})

target_include_directories("bootstrap" PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/drinli>"
)

target_compile_features("bootstrap" PUBLIC
    "cxx_std_20"
)

target_compile_options("bootstrap" PRIVATE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("bootstrap" PROPERTIES
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED YES
    INTERPROCEDURAL_OPTIMIZATION ${DRINLI_PERFORM_IPO}
)

#[=====[ Installation Configuration ]=====]

install(TARGETS "bootstrap"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/drinli"
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/drinli"
)
