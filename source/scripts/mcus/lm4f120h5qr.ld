PROVIDE_HIDDEN(FLASH_SIZE = 256K);
PROVIDE_HIDDEN(ROM_SIZE = 496M);
PROVIDE_HIDDEN(RAM_SIZE = 32K);

MEMORY
{
    FLASH (RX)  : ORIGIN = 0x00000000, LENGTH = FLASH_SIZE
    ROM   (RX)  : ORIGIN = 0x01000000, LENGTH = ROM_SIZE
    RAM   (RWX) : ORIGIN = 0x20000000, LENGTH = RAM_SIZE
}

SECTIONS
{
    .rom (NOLOAD) : ALIGN(4) {
        . += 0x10;

        HIDDEN(_rom_version = .);

        HIDDEN(_rom_gpio_table = . + 4 * 4);
        HIDDEN(_rom_system_control_table = . + 13 * 4);
        /* HIDDEN(_rom_api_table_base_address = .); */
    } > ROM
}