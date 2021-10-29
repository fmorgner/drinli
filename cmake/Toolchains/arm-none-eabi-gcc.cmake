set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")

set(CROSS_GCC_PREFIX "arm-none-eabi-")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(CMAKE_OBJDUMP "${CROSS_GCC_PREFIX}objdump" DOC "Path to ${CROSS_GCC_PREFIX}objdump")
find_program(CMAKE_OBJCOPY "${CROSS_GCC_PREFIX}objcopy" DOC "Path to ${CROSS_GCC_PREFIX}objcopy")
find_program(CMAKE_NM "${CROSS_GCC_PREFIX}nm" DOC "Path to ${CROSS_GCC_PREFIX}nm")
find_program(CMAKE_CXX_COMPILER_RANLIB "${CROSS_GCC_PREFIX}ranlib" DOC "Path to ${CROSS_GCC_PREFIX}ranlib")
find_program(CMAKE_STRIP "${CROSS_GCC_PREFIX}strip" DOC "Path to ${CROSS_GCC_PREFIX}strip")
find_program(CMAKE_LINKER "${CROSS_GCC_PREFIX}ld" DOC "Path to ${CROSS_GCC_PREFIX}ld")
find_program(CMAKE_CXX_COMPILER_AR "${CROSS_GCC_PREFIX}ar" DOC "Path to ${CROSS_GCC_PREFIX}ar")
find_program(CMAKE_CXX_COMPILER "${CROSS_GCC_PREFIX}g++" DOC "Path to ${CROSS_GCC_PREFIX}g++")

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")
set(BASE_COMPILER_FLAGS "${MCU_FLAGS} -fdata-sections -ffunction-sections")
set(BASE_COMPILER_FLAGS_DEBUG "-g -ggdb3")

set(CMAKE_ASM_FLAGS "${BASE_COMPILER_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "ASM Compiler Flags")
set(CMAKE_C_FLAGS "${BASE_COMPILER_FLAGS}" CACHE INTERNAL "C Compiler Flags")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${BASE_COMPILER_FLAGS_DEBUG}" CACHE INTERNAL "C Compiler Flags (Debug Mode)")
set(CMAKE_CXX_FLAGS "${BASE_COMPILER_FLAGS} -fno-rtti -fno-exceptions -fno-unwind-tables" CACHE INTERNAL "C++ Compiler Flags")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${BASE_COMPILER_FLAGS_DEBUG}" CACHE INTERNAL "C++ Compiler Flags (Debug Mode)")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -specs=nano.specs -Wl,--gc-sections -fuse-linker-plugin " CACHE INTERNAL "Executable Linker Flags")
