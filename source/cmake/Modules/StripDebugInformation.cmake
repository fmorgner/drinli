function(strip_debug_information TARGET)
    add_custom_command(TARGET "${TARGET}"
        POST_BUILD
        COMMAND "${CMAKE_OBJCOPY}"
        ARGS "--strip-debug" "$<TARGET_FILE:${TARGET}>"
        COMMENT "Stripping debug symbols from '${TARGET}' ..."
    )
endfunction()