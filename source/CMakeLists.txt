cmake_minimum_required(VERSION "3.21.0")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Toolchains/gcc.cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

project("Drinli"
    LANGUAGES CXX
    VERSION "1.0.0"
    DESCRIPTION "An experiment in building a bare-metal firmware for ARM systems"
)

#[=====[ Project modules ]=====]

include("AddFirmware")

#[=====[ Project configuration options and variables ]=====]

include("LinkerScript")
include("StackSize")

option(DRINLI_PERFORM_IPO "Perform interprocedural optimization" YES)

#[=====[ Generated project files ]=====]

write_linker_script()

#[=====[ TI ROM interface library ]=====]

add_library("ti-rom" INTERFACE)

target_include_directories("ti-rom" SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>"
)

target_compile_features("ti-rom" INTERFACE
    "cxx_std_20"
)

target_compile_options("ti-rom" INTERFACE
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("ti-rom" PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED YES
)

add_library("drinli::rom" ALIAS "ti-rom")

#[=====[ Drinli Base library ]=====]

file(GLOB BASE_SOURCE_FILES
    CONFIGURE_DEPENDS
    RELATIVE "${PROJECT_SOURCE_DIR}"
    "src/base/**.cpp"
    "include/base/**.hpp"
)

add_library("drinli-base" OBJECT
    ${BASE_SOURCE_FILES}
)

target_link_libraries("drinli-base" PUBLIC
    "drinli::rom"
)

target_include_directories("drinli-base" SYSTEM PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>"
)

target_compile_features("drinli-base" PUBLIC
    "cxx_std_20"
)

target_compile_options("drinli-base" PUBLIC
    "$<$<CXX_COMPILER_ID:GNU>:-Wall>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wextra>"
    "$<$<CXX_COMPILER_ID:GNU>:-Werror>"
    "$<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wstack-usage=${DRINLI_STACK_SIZE}>"
)

set_target_properties("drinli-base" PROPERTIES
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED YES
    INTERPROCEDURAL_OPTIMIZATION ${DRINLI_PERFORM_IPO}
)

add_library("drinli::base" ALIAS "drinli-base")

#[=====[ Application ]=====]

file(GLOB APP_SOURCE_FILES CONFIGURE_DEPENDS
    RELATIVE "${PROJECT_SOURCE_DIR}"
    "include/app/**.hpp"
    "src/app/**.cpp"
)

add_firmware("app"
    ${APP_SOURCE_FILES}
)

target_include_directories("app" PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
