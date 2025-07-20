extern "C" void construct_global_obj();

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib.hpp"
#include "string.hpp"
#include "malloc.hpp"

#if defined(__linux__)
#error "not using cross-compiler"
#endif

#if !defined(__i386__)
#error "needs to be compiled with ix86-elf compiler"
#endif

#define HEAP_SIZE 0x10000;


__attribute__((constructor)) void construct_global_obj() {
    // setup globals here

}


int kernel_main(void) {
    // initialize terminal interface
    terminal_initialize();

    // implement newline support
    terminal_writestring("Welcome to HermesOS\n");
    terminal_setcolor(VGA_COLOR_GREEN);

    extern char _end;
    uintptr_t heap_start = reinterpret_cast<uintptr_t> (&_end);
    uintptr_t heap_end_ptr = reinterpret_cast<uintptr_t> (&_end) + HEAP_SIZE;
    
    char heap_start_addr_str[16];
    hex_to_str(heap_start, heap_start_addr_str);
    
    terminal_writestring("Heap start addr: ");
    terminal_writestring(heap_start_addr_str);
    terminal_writestring("\n");

    char heap_end_addr_str[16];
    hex_to_str(reinterpret_cast<uintptr_t>(heap_end_ptr), heap_end_addr_str);   

    terminal_writestring("Heap end addr  : ");
    terminal_writestring(heap_end_addr_str);
    terminal_writestring("\n");

    malloc(12);

    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    terminal_writestring("Finished\n");
    
    return 0;
}
