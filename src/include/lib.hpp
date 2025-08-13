#ifndef LIB_HPP
#define LIB_HPP

#include <stddef.h>

void int_to_str(int data, char* s);
void hex_to_str(int data, char* s);

void* memcpy(void* dest, void* src, size_t count);
int memcmp(void* ptr1, void* ptr2, size_t num);
void* memmove(void* dest, void* src, size_t num);
void* memset(void* ptr, int value, size_t num);

#endif