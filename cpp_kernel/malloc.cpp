#include "malloc.hpp"

extern char _end;
uintptr_t heap_start = reinterpret_cast<uintptr_t> (&_end);
uintptr_t heap_end_ptr = reinterpret_cast<uintptr_t> (&_end) + HEAP_SIZE;

uintptr_t current = reinterpret_cast<uintptr_t> (&_end);

void* global_head = NULL;

#define BLOCK_SIZE = sizeof(struct data_block);


void* sbrk(size_t size) {

}

void* malloc(size_t size) {

}