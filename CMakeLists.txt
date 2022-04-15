cmake_minimum_required(VERSION "3.21.0")

#[============================================================================[
                                    Drinli
#]============================================================================]

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Drinli: No toolchain defined. Falling back to default!")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/Toolchains/arm-none-eabi-gcc.cmake")
endif()

project("Drinli"
    LANGUAGES CXX
    VERSION "1.0.0"
    DESCRIPTION "An experiment in building a bare-metal firmware for ARM systems"
)

#[=====[ Basic Project Configuration ]=====]

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Configuration"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#[=====[ Basic Project Configuration ]=====]

include("MCUs")
include("StackSize")
include("ConfigureLinkerScript")
include("ShowConfiguration")

option(DRINLI_PERFORM_IPO "Perform interprocedural optimization" YES)

drinli_configure_linker_script()
drinli_show_configuration()

#[=====[ External Dependencies ]=====]

find_package("Doxygen")
find_package("Sphinx")

#[=====[ Global Helper Definitions ]=====]

add_compile_definitions(
    "$<$<CXX_COMPILER_ID:GNU,Clang>:DRINLI_UNREACHABLE=__builtin_unreachable>"
)

#[=====[ Project Components ]=====]

add_subdirectory("source/bootstrap")
add_subdirectory("source/platform")
add_subdirectory("source/rom")
add_subdirectory("source/support")

#[=====[ Example Applications ]=====]

add_subdirectory("source/examples")

#[=====[ Documentation ]=====]

if(DOXYGEN_FOUND AND SPHINX_FOUND)
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_XML YES)
    set(DOXYGEN_XML_OUTPUT "doxml")
    set(DOXYGEN_QUIET YES)
    set(DOXYGEN_EXCLUDE_SYMBOLS "detail")
    set(DOXYGEN_WARN_LOGFILE "${PROJECT_BINARY_DIR}/doxygen.log")

    doxygen_add_docs("drinli_docs" ALL)

    add_custom_command(TARGET "drinli_docs"
      POST_BUILD
      COMMAND "${SPHINX_EXECUTABLE}"
      "-b" "html"
      "-D" "release=${PROJECT_VERSION}"
      "-D" "project=${PROJECT_NAME}"
      "-D" "breathe_projects.${PROJECT_NAME}=${PROJECT_BINARY_DIR}/${DOXYGEN_XML_OUTPUT}"
      "-D" "breathe_default_project=${PROJECT_NAME}"
      "-w" "sphinx.log"
      "-q"
      "${PROJECT_SOURCE_DIR}/docs"
      "${PROJECT_BINARY_DIR}/docs"
      WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
      COMMENT "Generating API documentation"
    )

endif()