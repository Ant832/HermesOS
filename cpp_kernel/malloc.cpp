#include "malloc.hpp"

extern char _end;
uintptr_t heap_start = reinterpret_cast<uintptr_t> (&_end);
uintptr_t heap_end_ptr = reinterpret_cast<uintptr_t> (&_end) + HEAP_SIZE;

uintptr_t current = reinterpret_cast<uintptr_t> (&_end);



data_block* global_head = NULL;

void* sbrk(size_t size) {

    for (unsigned int i = 0; i < size; ++i) {
        ++current;
    }

    data_block* current = global_head;
    while (current->next) {
        current = current->next;
    }

    return (void*)current;

}

data_block* find_free(size_t size) {
    data_block* current = global_head;
    while (current && !current->free && current->size >= size) {
        current = current->next;
    }

    return current;
}

data_block* request_space(data_block* last, size_t size) {
    data_block* block = (data_block*)sbrk(0);
    void* request = sbrk(size + sizeof(data_block));
    if ((void*)block != request) {
        terminal_writestring("error from request space\n");
        return NULL; // failed to allocate space
    }

    if (last) {
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->hint = 0x12345678;
    return block;
}

void* kmalloc(size_t size) {
    // if size is <= 0, return null
    if (size <= 0) {
        terminal_writestring("error 0\n");
        return NULL;
    }


    data_block* block;
    // else, check if free block of size is available and retrun
    if (!global_head) {
        block = request_space(NULL, size);
        if (!block) {
            terminal_writestring("error 1\n");
            return NULL;
        }
        block->size = size;
        block->next = NULL;
        block->free = 0;
        block->hint = 0x11111111;
        global_head = block;
    } else {
        // data_block* last = global_head;
        block = find_free(size);
        if (!block) {
            terminal_writestring("error 1\n");
            return NULL;
        } else {
            block->size = size;
            block->next = NULL;
            block->free = 0;
            block->hint = 0x77777777;
        }
    }

    //if no block, increment new space with ptr and return
    char hexStr[15];
    hex_to_str(block->hint, hexStr);
    terminal_writestring(hexStr);
    terminal_writestring("\n");

    return block + 1;
}