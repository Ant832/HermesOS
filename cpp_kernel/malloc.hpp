#ifndef MALLOC_HPP
#define MALLOC_HPP

#include <stddef.h>

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
    
}


#endif