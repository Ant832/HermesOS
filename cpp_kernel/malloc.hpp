#ifndef MALLOC_HPP
#define MALLOC_HPP

#include <stddef.h>
#include "string.hpp"
#include "lib.hpp"

#define HEAP_SIZE 0x10000;
extern char _end;
uintptr_t heap_start = reinterpret_cast<uintptr_t> (&_end);
uintptr_t heap_end_ptr = reinterpret_cast<uintptr_t> (&_end) + HEAP_SIZE;

uintptr_t current = reinterpret_cast<uintptr_t> (&_end);

void* sbrk(size_t size);

struct data_block {
    int* size;
    struct data_block* next;
    bool free;
};

class memList {
    data_block head;
public:
    memList() {

    }
};

void* malloc(size_t size) {
    void* heap_addr = sbrk(size);

    return heap_addr;
}

void* sbrk(size_t size) {

    for (unsigned int i = 0; i < size; ++i) {
        ++current;
    }

    return reinterpret_cast<void*> (current);
}


#endif