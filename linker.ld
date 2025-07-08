/* bootloader looks for marked entry point and starts execution */
ENTRY(_start)

/* identify where sections of the obj files will be in final kernel image */
SECTIONS {
    /* multiboot2 spec, kernel may be loaded within range of addresses
    will be able to relocate to run from loader-selected addresses
    loader has freedom in choosing span of memory which is 
    verified to be available by the firmware
    */
    . = 2M;

    /* multiboot header first, must be early in the image. Then .text section */
    .text BLOCK(4K) : ALIGN(4K) {
        /* aligns .text output section to 4 KB boundary
        logically (BLOCK(4K)) and in memory (ALIGN(4K))
        page alignment is typically 4KB */
        *(.multiboot)
        *(.text)
        /* tells linker to include all sections named .multiboot from all obj files
        (typically this section contains the multiboot header so GRUB can load
        the kernel correctly)
        and all .text sections (code (functions/instrutions)) */
    }

    /* read only data */
    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    /* read write data initialized */
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    /* read write data uninitialized and stack */
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMOM)
        *(.bss)
    }
    /* other sections may be included (made by compiler)
    add as needed */

    /* Include list of initialization functions sorted */
    .init_array : {
        crti.o(.init_array)
        KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .init_array.*)))
        KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .init_array))
        crtn.o(.init_array)
    }

    /* Include list of termination functions sorted */
    .fini_array : {
        crti.o(.fini_array)
        KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .fini_array.*)))
        KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .fini_array))
        crtn.o(.fini_array)
    }
}