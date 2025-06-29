/* Declare constants for multiboot header */
.set ALIGN,     1<<0            /* align loaded modules on page boundarues */
.set MEMINFO,   1<<1            /* provide memory map */
.set FLAGS,     ALIGN | MEMINFO /* multiboot 'flag' field */
.set MAGIC,     0x1BADB002      /* 'magic number' lets bootloader find header' */
.set CHECKSUM,  -(MAGIC+FLAGS)  /* checksum of above, to prove multiboot */

/*
Declare a multiboot header that marks the program as a kernel.
Values documented in multiboot standard.
Bootloader searches first 8 KiB of kernel file
This signature is in its own section to be forced in first 8 KiB of
the kernel file.
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
Kernel must provide a stack
Allocates a small stack with a symbol at the bottom, 16384 allocated
bytes, and a symbol at the top.
Stack grows downward on x86, must be 16-byte aligned
*/
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    /*
    
    */