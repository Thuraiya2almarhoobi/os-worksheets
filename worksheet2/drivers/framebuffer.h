#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// Function to write a character to a specific framebuffer cell
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

// Function to move the framebuffer cursor to a specific position
void fb_move_cursor(unsigned short pos);

// Function to move the cursor to (x, y) in the framebuffer
void fb_move(unsigned short x, unsigned short y);

// Function to set the foreground and background colors
void fb_set_color(unsigned char fg, unsigned char bg);

// Function to write a string to the framebuffer at the current cursor position
void fb_write_string(const char *str);

// Function to write an integer to the framebuffer
void fb_write_number(int num);

// Function to clear the framebuffer
void fb_clear();

#endif

