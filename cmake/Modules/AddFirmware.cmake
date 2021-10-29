function(drinli_add_firmware NAME)
    set(ELF_NAME "${NAME}.elf")
    set(DEBUG_SYMBOL_NAME "${NAME}.dsym")
    set(INTEL_HEX_NAME "${NAME}.hex")
    set(BINARY_NAME "${NAME}.bin")

    add_executable("${NAME}" ${ARGN})

    target_link_libraries("${NAME}" PUBLIC
        "-Wl,--whole-archive"
        "drinli::bootstrap"
        "-Wl,--no-whole-archive"
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

    add_custom_command(TARGET "${NAME}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "--only-keep-debug" "$<TARGET_FILE:${NAME}>" "${DEBUG_SYMBOL_NAME}"
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "--strip-debug" "$<TARGET_FILE:${NAME}>"
        COMMENT "Extracting debug symbols to '${DEBUG_SYMBOL_NAME} ..."
    )

    add_custom_command(TARGET "${NAME}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "-O" "binary" "-S" "$<TARGET_FILE:${NAME}>" "${BINARY_NAME}"
        COMMENT "Creating flashable binary file '${BINARY_NAME}' ..."
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )

    add_custom_command(TARGET "${NAME}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "-O" "binary" "-S" "$<TARGET_FILE:${NAME}>" "${INTEL_HEX_NAME}"
        COMMENT "Creating flashable Intel hex file '${INTEL_HEX_NAME}' ..."
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )

    add_custom_target("flash_${NAME}"
        COMMAND "openocd" "-f" "${PROJECT_SOURCE_DIR}/openocd.cfg" "-c" "program $<TARGET_FILE:${NAME}> verify reset exit"
        DEPENDS "${NAME}"
        COMMENT "Programming device with firmware ${ELF_NAME} ..."
    )
endfunction()
