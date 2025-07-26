#ifndef MALLOC_HPP
#define MALLOC_HPP

#include <stddef.h>
#include "terminal.hpp"
#include "lib.hpp"

struct data_block {
    size_t size;
    struct data_block* next;
    bool free;
    int hint; // debug purposes
};

#define HEAP_SIZE 0x10000;
#define BLOCK_SIZE sizeof(data_block);

extern char _end;
extern uintptr_t heap_start;
extern uintptr_t heap_end_ptr;
extern uintptr_t current;

extern data_block* global_head;

void* sbrk(size_t size);
data_block* find_free(size_t size);
data_block* request_space(data_block* last, size_t size);
void* kmalloc(size_t size);
void kfree(data_block data);

#endif