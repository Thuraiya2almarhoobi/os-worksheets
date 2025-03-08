ENTRY(loader) /* Specifies the entry point (label `loader` in `loader.asm`) */

SECTIONS {
    /* Load code starting at 1 MB */
    . = 0x00100000;

    /* Text section (executable code) aligned at 4 KB */
    .text ALIGN(0x1000) : {
        *(.text) /* Includes all `.text` sections from all object files */
    }

    /* Read-only data section aligned at 4 KB */
    .rodata ALIGN(0x1000) : {
        *(.rodata*) /* Includes all `.rodata` sections from all object files */
    }

    /* Data section aligned at 4 KB */
    .data ALIGN(0x1000) : {
        *(.data) /* Includes all `.data` sections from all object files */
    }

    /* BSS section (uninitialized data) aligned at 4 KB */
    .bss ALIGN(0x1000) : {
        *(COMMON) /* Includes all `COMMON` sections from all object files */
        *(.bss) /* Includes all `.bss` sections from all object files */
    }
}
