function(drinli_show_configuration)
    macro(_message_configuration MESSAGE)
        message(STATUS "Drinli: ${MESSAGE}")
    endmacro()

    if(DRINLI_PERFORM_IPO)
        _message_configuration("Interprocedural optimization (ITO/LTO) is enabled")
    else()
        _message_configuration("Interprocedural optimization (ITO/LTO) is disabled")
    endif()

    _message_configuration("Initial stack size is set to ${DRINLI_STACK_SIZE} bytes")
    _message_configuration("Using script '${DRINLI_LINKER_SCRIPT}' during linking of firmwares")
endfunction()
