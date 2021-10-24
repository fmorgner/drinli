include("AddFlashTarget")
include("CreateBinary")
include("CreateIntelHex")
include("ExtractDebugInformation")
include("StripDebugInformation")

function(add_firmware NAME)
    add_executable("${NAME}"
        ${ARGN}
    )

    target_link_libraries("${NAME}" PRIVATE
        "drinli::base"
        "drinli::rom"
    )

    target_link_options("${NAME}" PUBLIC
        "$<BUILD_INTERFACE:-T${_LINKER_SCRIPT_OUTPUT}>"
    )

    set_target_properties("${NAME}" PROPERTIES
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF
        INTERPROCEDURAL_OPTIMIZATION ${DRINLI_PERFORM_IPO}
        LINK_DEPENDS "${_LINKER_SCRIPT_OUTPUT}"
        SUFFIX ".elf"
    )

    extract_debug_information("${NAME}")
    strip_debug_information("${NAME}")

    create_binary("${NAME}")
    create_intel_hex("${NAME}")

    add_flash_target("${NAME}")
endfunction()
