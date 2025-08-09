#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <stddef.h>
#include <stdint.h>
#include "lib.hpp"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,

};

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

size_t strlen(const char* str);
void terminal_initialize();
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void scroll_up_one();
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

class outstream {
    char* buffer[50];

public:

    outstream& operator<<(const char data[]) {
        terminal_writestring(data);
        return *this;
    }


    outstream& operator<<(int data) {
        char string[15];
        int_to_str(data, string);
        terminal_writestring(string);
        return *this;
    }

    outstream& operator<<(outstream& (*function)(outstream&)) {

        return function(*this);
    }

    outstream& operator<<(char data) {
        char buf[2] = {data, '\0'};
        terminal_writestring(buf);
        return *this;
    }

};

inline outstream& endl(outstream& cout) {
    return cout << "\n";  // needs carriage return?
}

#endif