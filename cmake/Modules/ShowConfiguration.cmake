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
    _message_configuration("Targeting '${DRINLI_MCU}' during linking of firmwares")
endfunction()
