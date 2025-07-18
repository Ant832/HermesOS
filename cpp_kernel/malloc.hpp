#ifndef MALLOC_HPP
#define MALLOC_HPP

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


#endif