function(drinli_configure_linker_script)
    if(NOT DRINLI_STACK_SIZE)
        message(FATAL_ERROR "Drinli: Stack size has not been defined!")
    endif()

    if(NOT DRINLI_MCU)
        message(FATAL_ERROR "Drinli: No MCU has been selected!")
    endif()

    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/source/scripts/drinli.ld"
        "${PROJECT_BINARY_DIR}/scripts/drinli.ld"
        @ONLY
    )
endfunction()