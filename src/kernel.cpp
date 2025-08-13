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

outstream cout;

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

    char name[] = "my name is ";
    char letter = 't';
    cout << "Hello " << name << 'a' << 'n' << letter << 1234 << endl;

    char str[] = "almost every programmer should know memset!";
    memset(str,'-',6);
    cout << str << endl;

    char str2[] = "memmove can be very useful......";
    memmove(str2+15,str2+20,11);
    cout << str2 << endl;

    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";

    int n;

    n=memcmp ( buffer1, buffer2, sizeof(buffer1) );

    if (n>0) cout << buffer1 << " is greater than " << buffer2 << endl;
    else if (n<0) cout << buffer1 << " is less than " << buffer2 << endl;
    else cout << buffer1 << " is the same as " << buffer2 << endl;

    struct {
        char name[40];
        int age;
    } person, person_copy;

    char myname[] = "Pierre de Fermat";

    /* using memcpy to copy string: */
    memcpy ( person.name, myname, strlen(myname)+1 );
    person.age = 46;

    /* using memcpy to copy structure: */
    memcpy ( &person_copy, &person, sizeof(person) );

    cout << "person_copy: " << person_copy.name << ", " << person_copy.age << endl;



    terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
    terminal_writestring("Finished\n");

    return 0;
}
