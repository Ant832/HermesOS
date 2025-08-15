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

// TODO: implement memcpy, memcmp
void* memset(void* ptr, int value, size_t num) {
    unsigned char* buffer = (unsigned char*)ptr;
    for (size_t i = 0; i < num; ++i) {
        buffer[i] = (unsigned char) value;
    }
    return ptr;
}

void* memmove(void* dest, void* src, size_t num) {
    unsigned char* u_src = (unsigned char*) src;
    unsigned char* u_dest = (unsigned char*) dest;

    if (src > dest) {
        for (size_t i = 0; i < num; ++i) {
            u_dest[i] = u_src[i];
        }
    } else {
        for (size_t i = num; i > 0; --i) {
            u_dest[i - 1] = u_src[i - 1];
        }
    }
    return dest;
}


int memcmp(void* ptr1, void* ptr2, size_t num) {
    unsigned char* u_ptr1 = (unsigned char*) ptr1;
    unsigned char* u_ptr2 = (unsigned char*) ptr2;
    for (size_t i = 0; i < num; ++i) {
        if (u_ptr1[i] == u_ptr2[i]) {
            continue;
        } else if (u_ptr1[i] > u_ptr2[i]) {
            return 1;
        } else {
            return -1;
        }
    }

    return 0;
}


void* memcpy(void* dest, void* src, size_t num) {
    unsigned char* u_src = (unsigned char*) src;
    unsigned char* u_dest = (unsigned char*) dest;

    for (size_t i = 0; i < num; ++i) {
        u_dest[i] = u_src[i];
    }

    return dest;
}