function(create_intel_hex TARGET)
    set(OUTPUT_FILE_NAME "${TARGET}.hex")

    add_custom_command(TARGET "${TARGET}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "-O" "ihex" "-S" "$<TARGET_FILE:${TARGET}>" "${OUTPUT_FILE_NAME}"
        COMMENT "Creating flashable Intel HEX file '${OUTPUT_FILE_NAME}' ..."
    )
endfunction()