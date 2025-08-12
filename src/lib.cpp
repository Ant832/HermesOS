#include "lib.hpp"
 #include "terminal.hpp" // debug purposes
#include <stddef.h>

void int_to_str(int data, char* s) {
    static_assert(-5 % 3 == -2);
    if (data < 0) {
        *s++ = '-';
    } else {
        data = -data;
    }
    int copy = data;
    do {
        ++s;
    }
    while (copy /= 10);
    *s = '\0';
    do {
        *--s = '0' - data % 10;
    }
    while (data /= 10);
}

void hex_to_str(int data, char* s) {
    *s++ = '0';
    *s++ = 'x';
    if (data == 0) {
        *s++ = '0';
        *s = '\0';
        return;
    }
    char characters[16] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    int copy = data;
    do {
        ++s;
    }
    while (copy /= 16);
    *s = '\0';
    do {
        *--s = characters[data % 16];
    }
    while (data /= 16);
}

// TODO: implement memcpy, memcmp, memmove, and memset
void* memcpy(void* dest, void* src, size_t count) {
    outstream cout2;
    cout2 << "test" << endl;
    void* a;
    return a;
}