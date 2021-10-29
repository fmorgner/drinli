if(NOT DRINLI_STACK_SIZE)
    set(_STACK_SIZE "256" CACHE INTERNAL "Active size of the system stack")
else()
    set(_STACK_SIZE "${DRINLI_STACK_SIZE}" CACHE INTERNAL "Active size of the system stack")
endif()

math(EXPR _STACK_SIZE "${_STACK_SIZE}" OUTPUT_FORMAT DECIMAL)

set(DRINLI_STACK_SIZE "${_STACK_SIZE}" CACHE STRING "Size of the system stack in bytes")