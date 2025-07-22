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

__attribute__((constructor)) void construct_global_obj() {
    // setup globals here

}

int kernel_main(void) {
    // initialize terminal interface
    terminal_initialize();

    // implement newline support
    terminal_writestring("Welcome to HermesOS\n");
    terminal_setcolor(VGA_COLOR_GREEN);

    char* myString = (char*) malloc((10 + 1)*sizeof(char)); // allocate space for 10 digits + '\n' + '\0'
    
    for (unsigned int i = 0; i < 10; ++i) {
        *(myString + i) = 'A';
    }
    *(myString + 10) = '\0';
    for (unsigned int i = 0; i < 10; ++i) {
        terminal_writestring(myString + i);
    }
    terminal_writestring("\n");

    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    terminal_writestring("Finished\n");
    
    return 0;
}
