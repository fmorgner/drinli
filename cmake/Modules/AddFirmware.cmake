function(drinli_add_firmware NAME)
    set(ELF_NAME "${NAME}.elf")
    set(DEBUG_SYMBOL_NAME "${NAME}.dsym")
    set(INTEL_HEX_NAME "${NAME}.hex")
    set(BINARY_NAME "${NAME}.bin")

    list(APPEND LINKER_SCRIPTS
        "${PROJECT_BINARY_DIR}/scripts/drinli.ld"
        "${PROJECT_SOURCE_DIR}/source/scripts/mcus/${DRINLI_MCU}.ld"
    )

    add_executable("${NAME}" ${ARGN})

    target_link_libraries("${NAME}" PUBLIC
        "-Wl,--whole-archive"
        "drinli_bootstrap"
        "-Wl,--no-whole-archive"
        "drinli_mcu"
        "drinli_platform"
        "drinli_rom"
    )

    target_link_directories("${NAME}" PUBLIC
        "${PROJECT_BINARY_DIR}/scripts"
        "${PROJECT_SOURCE_DIR}/source/scripts/mcus"
    )

    target_link_options("${NAME}" PUBLIC
        "$<BUILD_INTERFACE:-Tdrinli.ld>"
    )

    set_target_properties("${NAME}" PROPERTIES
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF
        INTERPROCEDURAL_OPTIMIZATION ${DRINLI_PERFORM_IPO}
        LINK_DEPENDS "${LINKER_SCRIPTS}"
        SUFFIX ".elf"
    )

    add_custom_command(TARGET "${NAME}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "--only-keep-debug" "$<TARGET_FILE:${NAME}>" "${DEBUG_SYMBOL_NAME}"
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "--strip-debug" "$<TARGET_FILE:${NAME}>"
        COMMENT "Extracting debug symbols to '${DEBUG_SYMBOL_NAME} ..."
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
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
        ARGS "-O" "ihex" "-S" "$<TARGET_FILE:${NAME}>" "${INTEL_HEX_NAME}"
        COMMENT "Creating flashable Intel hex file '${INTEL_HEX_NAME}' ..."
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )

    add_custom_command(TARGET "${NAME}"
        POST_BUILD
        COMMAND "${CMAKE_SIZE}"
        ARGS "--format=berkeley" "$<TARGET_FILE:${NAME}>"
        COMMENT "Dumping section sizes of '${NAME}' ..."
        WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )

    add_custom_target("flash_${NAME}"
        COMMAND "openocd" "-f" "${PROJECT_SOURCE_DIR}/openocd.cfg" "-c" "program $<TARGET_FILE:${NAME}> verify reset exit"
        DEPENDS "${NAME}"
        COMMENT "Programming device with firmware ${ELF_NAME} ..."
    )
endfunction()
