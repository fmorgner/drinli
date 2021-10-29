function(drinli_glob_component_sources OUTPUT_VARIABLE)
    file(GLOB_RECURSE COMPONENT_SOURCES
        CONFIGURE_DEPENDS
        "*.[ch]pp"
    )
    set(${OUTPUT_VARIABLE} ${COMPONENT_SOURCES} PARENT_SCOPE)
endfunction()

