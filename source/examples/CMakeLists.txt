
cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")

#[============================================================================[
                              The Drinli Demo App
#]============================================================================]

#[=====[ CMake Dependencies ]=====]

include("AddFirmware")

#[=====[ LED Blinker Application ]=====]

drinli_add_firmware("blinky" "src/blinky.cpp")