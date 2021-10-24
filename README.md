Drinli
======

This is an experiment in writing a bare-metal firmware for ARM embedded systems.

Building
--------

Prerequisites:
  - CMake >= 3.20
  - arm-none-eabi-gcc >= 11.2
  - arm-none-eabi-newlib >= 4.1
  - arm-none-eabi-binutils >= 2.37

Instructions:
  - configure: `$ cmake -S source -B build -DCMAKE_BUILD_TYPE=MinSizeRel`
  - build: `$ cmake --build build`

Flashing
--------

Prerequisites:
  - Built firmware image (see above)
  - openocd >= 0.11

Instructions:
  - flashing: `$ cmake --build build --target flash_app`