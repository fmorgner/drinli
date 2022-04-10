PROVIDE_HIDDEN(STACK_SIZE = @DRINLI_STACK_SIZE@);

INCLUDE "@DRINLI_MCU@.ld"

SECTIONS
{
    .vector_table : ALIGN(4) {
        KEEP(*(.initial_stack))
        KEEP(*(.interrupt_vectors))
    } > FLASH

    . = 0x26d;

    .text : ALIGN(4) {
        *(.text .text.* .gnu.linkonce.t.*)
        *(.rodata .rodata.* .gnu.linkonce.r.*)

        . = ALIGN(4);
        HIDDEN(_preinit_array_start = .);
        KEEP(*(.preinit_array))
        HIDDEN(_preinit_array_end = .);

        . = ALIGN(4);
        HIDDEN(_init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        HIDDEN(_init_array_end = .);
    } > FLASH

    .data : AT(ADDR(.text) + SIZEOF(.text)) {
        HIDDEN(_data_start = .);
        *(.data .data.*)
        . = ALIGN(4);
        HIDDEN(_data_end = .);
    } > RAM

    HIDDEN(_data_load_point = LOADADDR(.data));

    .bss (NOLOAD) : {
        . = ALIGN(4);
        HIDDEN(_bss_start = .);
        *(.bss .bss.*)
        . = ALIGN(4);
        HIDDEN(_bss_end = .);
    } > RAM

    .stack (NOLOAD) : ALIGN(8) {
        . = . + STACK_SIZE;
        HIDDEN(_initial_stack_end = .);
    } > RAM

    . = ALIGN(4);
    HIDDEN(_heap_start = .);
    . = ADDR(.data) + RAM_SIZE;
    HIDDEN(_head_end = .);

    /DISCARD/ : {
        *(.init)
        *(.fini)
        *(.fini_array)
        *(.fini_array.*)
        *(.dtors)
        *(dtors.*)
    }
}
