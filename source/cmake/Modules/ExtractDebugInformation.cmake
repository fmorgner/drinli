function(extract_debug_information TARGET)
    set(OUTPUT_FILE_NAME "${TARGET}.dsym")

    add_custom_command(TARGET "${TARGET}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "--only-keep-debug" "$<TARGET_FILE:${TARGET}>" "${OUTPUT_FILE_NAME}"
        COMMENT "Extracting debug symbols '${OUTPUT_FILE_NAME}' ..."
    )
endfunction()