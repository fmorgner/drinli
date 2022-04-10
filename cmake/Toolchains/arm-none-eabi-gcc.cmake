set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")

set(CMAKE_CXX_COMPILER_TARGET "arm-none-eabi")

set(CROSS_GCC_PREFIX "${CMAKE_CXX_COMPILER_TARGET}-")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(CMAKE_CXX_COMPILER "${CROSS_GCC_PREFIX}g++" DOC "Path to ${CROSS_GCC_PREFIX}g++")
find_program(CMAKE_CXX_COMPILER_AR "${CROSS_GCC_PREFIX}ar" DOC "Path to ${CROSS_GCC_PREFIX}ar")
find_program(CMAKE_CXX_COMPILER_RANLIB "${CROSS_GCC_PREFIX}ranlib" DOC "Path to ${CROSS_GCC_PREFIX}ranlib")
find_program(CMAKE_LINKER "${CROSS_GCC_PREFIX}ld" DOC "Path to ${CROSS_GCC_PREFIX}ld")
find_program(CMAKE_NM "${CROSS_GCC_PREFIX}nm" DOC "Path to ${CROSS_GCC_PREFIX}nm")
find_program(CMAKE_OBJCOPY "${CROSS_GCC_PREFIX}objcopy" DOC "Path to ${CROSS_GCC_PREFIX}objcopy")
find_program(CMAKE_OBJDUMP "${CROSS_GCC_PREFIX}objdump" DOC "Path to ${CROSS_GCC_PREFIX}objdump")
find_program(CMAKE_SIZE "${CROSS_GCC_PREFIX}size" DOC "Path to ${CROSS_GCC_PREFIX}size")
find_program(CMAKE_STRIP "${CROSS_GCC_PREFIX}strip" DOC "Path to ${CROSS_GCC_PREFIX}strip")

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")

set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -fdata-sections -ffunction-sections -fno-rtti -fno-exceptions -fno-unwind-tables" CACHE STRING "C++ Compiler Flags")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb3" CACHE STRING "C++ Compiler Flags (Debug Mode)")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG" CACHE STRING "C++ Compiler Flags (Debug Mode)")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -DNDEBUG ${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "C++ Compiler Flags (Debug Mode)")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -specs=nano.specs -Wl,--gc-sections -fuse-linker-plugin " CACHE STRING "Executable Linker Flags")

mark_as_advanced(CMAKE_SIZE)