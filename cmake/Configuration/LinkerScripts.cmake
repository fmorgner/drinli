function(_write_linker_script INPUT_PATH OUTPUT_PATH)
    if(NOT DRINLI_STACK_SIZE)
        message(FATAL_ERROR "DRINLI_STACK_SIZE has not been set!")
    endif()

    configure_file("${INPUT_PATH}"
        "${OUTPUT_PATH}"
        @ONLY
    )
endfunction()

set(_LINKER_SCRIPTS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/source/scripts" CACHE INTERNAL "The directory containing the linker script source")
set(_LINKER_SCRIPTS_OUTPUT_DIR "${PROJECT_BINARY_DIR}/scripts" CACHE INTERNAL "The directory containing the linker script output")

file(GLOB _LINKER_SCRIPTS_SOURCES CONFIGURE_DEPENDS "${_LINKER_SCRIPTS_SOURCE_DIR}/*.ld.in")

foreach(SOURCE_FILE IN LISTS _LINKER_SCRIPTS_SOURCES)
    get_filename_component(SOURCE_NAME "${SOURCE_FILE}" NAME)
    string(REPLACE ".ld.in" "" SOURCE_NAME "${SOURCE_NAME}")
    list(APPEND _LINKER_SCRIPT_NAMES "${SOURCE_NAME}")
    _write_linker_script("${SOURCE_FILE}" "${_LINKER_SCRIPTS_OUTPUT_DIR}/${SOURCE_NAME}.ld")
endforeach()

list(GET _LINKER_SCRIPT_NAMES 0 _LINKER_SCRIPT_DEFAULT_NAME)
set(DRINLI_LINKER_SCRIPT "${_LINKER_SCRIPT_DEFAULT_NAME}" CACHE STRING "The linker script to use")
set_property(CACHE DRINLI_LINKER_SCRIPT PROPERTY
    STRINGS
    ${_LINKER_SCRIPT_NAMES}
)

set(DRINLI_LINKER_SCRIPT_PATH "${_LINKER_SCRIPTS_OUTPUT_DIR}/${DRINLI_LINKER_SCRIPT}.ld")
