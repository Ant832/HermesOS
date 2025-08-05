extern "C" void construct_global_obj();

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lib.hpp"
#include "terminal.hpp"
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

    terminal_writestring("Welcome to HermesOS\n");
    terminal_setcolor(VGA_COLOR_GREEN);

    char* myString = (char*) kmalloc((5 + 1)*sizeof(char)); // allocate space for 5 letters + '\0'
    int character = 65;
    

    for (unsigned int i = 0; i < 5; ++i) {
        *(myString + i) = (char)character++;
    }
    *(myString + 5) = '\0';
    terminal_writestring(myString);
    terminal_writestring("\n");


    char* otherString = (char*) kmalloc(10 * sizeof(char));
    for (unsigned int i = 0; i < 9; ++i) {
        *(otherString + i) = '0' + i;
    }
    *(otherString + 9) = '\n';
    *(otherString + 10) = '\0';
    terminal_writestring(otherString);

    kfree(myString);
    kfree(otherString);

    outstream cout;
    const char* data = "a\n";
    cout << data;

    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    terminal_writestring("Finished\n");
    
    return 0;
}
