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

        HIDDEN(_rom_version                = . +  0 * 4);
        HIDDEN(_rom_uart_table             = . +  1 * 4);
        HIDDEN(_rom_ssi_table              = . +  2 * 4);
        HIDDEN(_rom_i2c_table              = . +  3 * 4);
        HIDDEN(_rom_gpio_table             = . +  4 * 4);
        HIDDEN(_rom_adc_table              = . +  5 * 4);
        HIDDEN(_rom_comparator_table       = . +  6 * 4);
        HIDDEN(_rom_flash_table            = . +  7 * 4);
        HIDDEN(_rom_pwm_table              = . +  8 * 4);
        HIDDEN(_rom_qei_table              = . +  9 * 4);
        HIDDEN(_rom_systick_table          = . + 10 * 4);
        HIDDEN(_rom_timer_table            = . + 11 * 4);
        HIDDEN(_rom_watchdog_table         = . + 12 * 4);
        HIDDEN(_rom_system_control_table   = . + 13 * 4);
        HIDDEN(_rom_interrupt_table        = . + 14 * 4);
        HIDDEN(_rom_ethernet_table         = . + 15 * 4);
        HIDDEN(_rom_usb_table              = . + 16 * 4);
        HIDDEN(_rom_udma_table             = . + 17 * 4);
        HIDDEN(_rom_can_table              = . + 18 * 4);
        HIDDEN(_rom_hibernate_table        = . + 19 * 4);
        HIDDEN(_rom_mpu_table              = . + 20 * 4);
        HIDDEN(_rom_software_table         = . + 21 * 4);
        HIDDEN(_rom_i2s_table              = . + 22 * 4);
        HIDDEN(_rom_epi_table              = . + 23 * 4);
        HIDDEN(_rom_eeprom_table           = . + 24 * 4);
        HIDDEN(_rom_fan_table              = . + 25 * 4);
        HIDDEN(_rom_fpu_table              = . + 26 * 4);
        HIDDEN(_rom_lpc_table              = . + 27 * 4);
        HIDDEN(_rom_peci_table             = . + 28 * 4);
        HIDDEN(_rom_smbus_table            = . + 29 * 4);
        HIDDEN(_rom_system_exception_table = . + 30 * 4);
    } > ROM
}
