function(add_flash_target TARGET)
    message(STATUS "Creating flash target (flash_${TARGET}) for '${TARGET}'")

    add_custom_target("flash_${TARGET}"
        COMMAND "openocd" "-f" "${PROJECT_SOURCE_DIR}/../openocd.cfg" "-c" "program $<TARGET_FILE:${TARGET}> verify reset exit"
        DEPENDS "app"
        COMMENT "Programming device ..."
    )
endfunction()