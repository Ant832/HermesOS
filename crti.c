typedef void (*func_ptr)(void);
typedef void (*ctor_ptr)(void);

extern func_ptr _init_array_start[0], _init_array_end[0];
extern func_ptr _fini_array_start[0], _fini_array_end[0];
extern ctor_ptr _init_array_start[], _init_array_end[];

void _init_array(void) {
    for (func_ptr* func = _init_array_start; func != _init_array_end; ++func) {
        (*func)();
    }
}

void _init_global_ctors() {
    for (ctor_ptr* ctor = _init_array_start; ctor <= _init_array_end; ++ctor) {
        (*ctor)();
    }
}

void _fini_array(void) {
    for (func_ptr* func = _fini_array_start; func != _fini_array_end; ++func) {
        (*func)();
    }
}

func_ptr _init_array_start[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(func_ptr)))) = { };
func_ptr _fini_array_start[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(func_ptr)))) = { };