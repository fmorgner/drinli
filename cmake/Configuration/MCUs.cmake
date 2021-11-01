set(_DRINLI_MCU_SEARCH_PATH "${PROJECT_SOURCE_DIR}/source/scripts/mcus"
    CACHE
    INTERNAL
    "The directory containing the MCU specific linker scripts"
)

file(GLOB _DRINLI_MCU_SCRIPTS CONFIGURE_DEPENDS "${_DRINLI_MCU_SEARCH_PATH}/*.ld")

foreach(MCU_SCRIPT IN LISTS _DRINLI_MCU_SCRIPTS)
    get_filename_component(MCU_NAME "${MCU_SCRIPT}" NAME)
    string(REPLACE ".ld" "" MCU_NAME "${MCU_NAME}")
    list(APPEND _DRINLI_MCUS "${MCU_NAME}")
endforeach()

list(GET _DRINLI_MCUS 0 _DRINLI_DEFAULT_MCU)
set(DRINLI_MCU "${_DRINLI_DEFAULT_MCU}"
    CACHE
    STRING
    "The linker script to use"
)
set_property(CACHE DRINLI_MCU PROPERTY
    STRINGS
    ${_DRINLI_MCUS}
)
