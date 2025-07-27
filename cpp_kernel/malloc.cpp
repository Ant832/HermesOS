#include "malloc.hpp"

extern char _end;
uintptr_t heap_start = reinterpret_cast<uintptr_t> (&_end);
uintptr_t heap_end_ptr = reinterpret_cast<uintptr_t> (&_end) + HEAP_SIZE;

uintptr_t heap_ptr = reinterpret_cast<uintptr_t> (&_end);



data_block *global_head = NULL;

void* sbrk(size_t size) {
    if (heap_ptr + size > heap_end_ptr) {
        return (void*) -1; // sbrk fail
    }

    uintptr_t prev = heap_ptr;

    for (unsigned int i = 0; i < size; ++i) {
        ++heap_ptr;
    }


    char debugStr[15];
    hex_to_str(int(heap_ptr), debugStr);
    terminal_writestring(debugStr);
    terminal_writestring("\n");

    return (void*)prev;

}

data_block* find_free(data_block **last, size_t size) {
    data_block *current = global_head;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }

    return current;
}

data_block* request_space(data_block *last, size_t size) {
    data_block *block = (data_block*)sbrk(0);
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
    if (size <= 0) {
        terminal_writestring("error trying to malloc size <= 0\n");
        return NULL;
    }


    data_block *block;
    if (!global_head) {
        block = request_space(NULL, size);
        if (!block) {
            terminal_writestring("no global head, block unavailable\n");
            return NULL;
        }
        block->size = size;
        block->next = NULL;
        block->free = 0;
        block->hint = 0x11111111;
        global_head = block;
    } else {
        data_block *last = global_head;
        block = find_free(&last, size);
        if (!block) {
            terminal_writestring("no free block\n");
            return NULL;
        } else {
            block->size = size;
            block->next = NULL;
            block->free = 0;
            block->hint = 0x77777777;
        }
    }


    return block + 1;
}

void kfree(void* data) {
    data_block *toFree = reinterpret_cast<data_block*>(data);

    char debugString[15];
    int_to_str(toFree->size, debugString);
    terminal_writestring(debugString);
    terminal_writestring("\n");

}