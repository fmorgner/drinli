function(create_binary TARGET)
    set(OUTPUT_FILE_NAME "${TARGET}.bin")

    add_custom_command(TARGET "${TARGET}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "-O" "binary" "-S" "$<TARGET_FILE:${TARGET}>" "${OUTPUT_FILE_NAME}"
        COMMENT "Creating flashable binary '${OUTPUT_FILE_NAME}' ..."
    )
endfunction()