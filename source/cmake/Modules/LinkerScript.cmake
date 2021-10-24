set(_LINKER_SCRIPT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/scripts" CACHE INTERNAL "The directory containing the linker script source")
set(_LINKER_SCRIPT_OUTPUT_DIR "${PROJECT_BINARY_DIR}/scripts" CACHE INTERNAL "The directory containing the linker script output")

file(GLOB _LINKER_SCRIPTS_SOURCES CONFIGURE_DEPENDS "${_LINKER_SCRIPT_SOURCE_DIR}/*.ld.in")
set(_LINKER_SCRIPT_SOURCES CACHE INTERNAL "All available linker script sources")
set(_LINKER_SCRIPT_NAMES CACHE INTERNAL "All available linker script names")

foreach(SOURCE_FILE IN LISTS _LINKER_SCRIPTS_SOURCES)
    get_filename_component(SOURCE_NAME "${SOURCE_FILE}" NAME)
    string(REPLACE ".ld.in" "" SOURCE_NAME "${SOURCE_NAME}")
    list(APPEND _LINKER_SCRIPT_NAMES "${SOURCE_NAME}")
endforeach()

list(GET _LINKER_SCRIPT_NAMES 0 _LINKER_SCRIPT_DEFAULT_NAME)
set(DRINLI_LINKER_SCRIPT "${_LINKER_SCRIPT_DEFAULT_NAME}" CACHE STRING "The linker script to use")

set_property(CACHE DRINLI_LINKER_SCRIPT PROPERTY
    STRINGS
    ${_LINKER_SCRIPT_NAMES}
)

set(_LINKER_SCRIPT_SOURCE "${_LINKER_SCRIPT_SOURCE_DIR}/${DRINLI_LINKER_SCRIPT}.ld.in" CACHE INTERNAL "Path to the linker script source file")
set(_LINKER_SCRIPT_OUTPUT "${_LINKER_SCRIPT_OUTPUT_DIR}/${DRINLI_LINKER_SCRIPT}.ld" CACHE INTERNAL "Path to the generated linker script")

function(write_linker_script)
    if(NOT DRINLI_STACK_SIZE)
        message(FATAL_ERROR "DRINLI_STACK_SIZE has not been set!")
    endif()

    configure_file("${_LINKER_SCRIPT_SOURCE}"
        "${_LINKER_SCRIPT_OUTPUT}"
        @ONLY
    )
endfunction()