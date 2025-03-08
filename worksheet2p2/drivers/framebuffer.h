#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// Framebuffer dimensions
#define FB_COLS 80
#define FB_ROWS 25

// Framebuffer colors
#define FB_GREEN 2
#define FB_DARK_GREY 8
#define FB_RED 4
#define FB_BLACK 0

// Function prototypes
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor(unsigned short pos);
void fb_move(unsigned short x, unsigned short y);
void fb_set_color(unsigned char fg, unsigned char bg);
void fb_write_string(const char *str);
void fb_write_number(int num);
void fb_clear();
void fb_backspace();

// Accessor functions for cursor position
unsigned short fb_get_cursor_x();
unsigned short fb_get_cursor_y();

#endif
