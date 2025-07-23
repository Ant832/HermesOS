#ifndef MALLOC_HPP
#define MALLOC_HPP

#include <stddef.h>
#include "terminal.hpp"
#include "lib.hpp"

#define HEAP_SIZE 0x10000;
extern char _end;
extern uintptr_t heap_start;
extern uintptr_t heap_end_ptr;

extern uintptr_t current;

extern void* global_head;

struct data_block {
    size_t size;
    struct data_block* next;
    bool free;
    int data;
};

#define BLOCK_SIZE = sizeof(struct data_block);

void* sbrk(size_t size);
void* malloc(size_t size);


#endif