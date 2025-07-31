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

    heap_ptr += size;

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
// TODO: check if block->next = NULL; is neccessary
void* kmalloc(size_t size) {
    if (size <= 0) {
        terminal_writestring("error trying to malloc size <= 0\n");
        return NULL;
    }


    data_block *block;
    if (!global_head) {


        char debugString[15];
        hex_to_str(heap_ptr, debugString);
        terminal_writestring("Start of Heap                     : ");
        terminal_writestring(debugString);
        terminal_writestring("\n");


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
            block = request_space(last, size);
            if (!block) {
                terminal_writestring("no free block\n");
                return NULL;
            }
        } else {

            block->size = size;
            block->next = NULL;
            block->free = 0;
            block->hint = 0x77777777;
        }
    }


    return block + 1;
}

data_block* get_data_block(void *data) {
    return (data_block*)data - 1;
}

void kfree(void *data) {
    if (!data ) {
        terminal_writestring("kfree() failed: null pointer\n");
        return;
    }
    data_block *struct_data = get_data_block(data);

    if ((uintptr_t)struct_data < heap_start || (uintptr_t)struct_data >= heap_end_ptr) {
        terminal_writestring("kfree() failed: data outside heap range\n");
        return;
    }

    struct_data->free = 1;
    struct_data->hint = 0x55555555;

    uintptr_t block_end = (uintptr_t)struct_data + sizeof(data_block) + struct_data->size;
    if (block_end == heap_ptr) {
        heap_ptr = (uintptr_t)struct_data;
    }



    char debugString[15];
    hex_to_str(int(struct_data), debugString);
    terminal_writestring("Heap space freed, new location   : ");
    terminal_writestring(debugString);
    terminal_writestring("\n");

}