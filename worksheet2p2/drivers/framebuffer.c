#include "./io.h"
#include <stddef.h>
#include "framebuffer.h"


/* The I/O ports */
#define FB_COMMAND_PORT    0x3D4
#define FB_DATA_PORT       0x3D5
/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND   14
#define FB_LOW_BYTE_COMMAND    15

#define FB_ADDRESS 0x000B8000
#define FB_ROWS 25
#define FB_COLS 80

// Global variables for cursor position and colors
static unsigned short cursor_x = 0;
static unsigned short cursor_y = 0;
static unsigned char foreground_color = 2; // Default: Green
static unsigned char background_color = 0; // Default: Black

/** fb_write_cell:
 * Writes a character with the given foreground and background color
 * to a specific position in the framebuffer.
 *
 * @param i The location in the framebuffer
 * @param c The character to write
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    volatile char *fb = (volatile char *)FB_ADDRESS;
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/** fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position.
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos & 0x00FF));
}

/** fb_move:
 * Moves the cursor to a given (x, y) position in the framebuffer.
 *
 * @param x The column position (0 to FB_COLS - 1)
 * @param y The row position (0 to FB_ROWS - 1)
 */
void fb_move(unsigned short x, unsigned short y) {
    cursor_x = x;
    cursor_y = y;
    unsigned short pos = y * FB_COLS + x;
    fb_move_cursor(pos);
}

/** fb_set_color:
 * Sets the foreground and background colors for subsequent writes.
 *
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_set_color(unsigned char fg, unsigned char bg) {
    foreground_color = fg;
    background_color = bg;
}

/** fb_get_cursor_x:
 * Retrieves the current x position of the cursor.
 *
 * @return The current x position of the cursor
 */
unsigned short fb_get_cursor_x() {
    return cursor_x;
}

/** fb_get_cursor_y:
 * Retrieves the current y position of the cursor.
 *
 * @return The current y position of the cursor
 */
unsigned short fb_get_cursor_y() {
    return cursor_y;
}

/** fb_write_string:
 * Writes a null-terminated string to the framebuffer at the current cursor position.
 *
 * @param str The string to write
 */
void fb_write_string(const char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            unsigned int pos = cursor_y * FB_COLS + cursor_x;
            fb_write_cell(pos, str[i], foreground_color, background_color);
            cursor_x++;
            if (cursor_x >= FB_COLS) {
                cursor_x = 0;
                cursor_y++;
            }
        }
        if (cursor_y >= FB_ROWS) {
            cursor_y = 0; // Wrap around for simplicity
        }
        fb_move(cursor_x, cursor_y);
    }
}

/** fb_backspace:
 * Handles backspace by moving the cursor back and clearing the character.
 */
void fb_backspace() {
    if (cursor_x > 0) {
        cursor_x--;
    } else if (cursor_y > 0) {
        cursor_y--;
        cursor_x = FB_COLS - 1;
    }
    unsigned int pos = cursor_y * FB_COLS + cursor_x;
    fb_write_cell(pos, ' ', foreground_color, background_color);
    fb_move(cursor_x, cursor_y);
}

/** itoa:
 * Converts an integer to a null-terminated string.
 *
 * @param value The integer to convert
 * @param buffer The buffer to store the resulting string
 * @param base The numerical base (e.g., 10 for decimal)
 */
void itoa(int value, char* buffer, int base) {
    char* ptr = buffer;
    char* ptr1 = buffer;
    char tmp_char;
    int tmp_value;

    if (value == 0) {
        *buffer++ = '0';
        *buffer = '\0';
        return;
    }

    while (value != 0) {
        tmp_value = value % base;
        value /= base;
        *ptr++ = (tmp_value < 10) ? (tmp_value + '0') : (tmp_value - 10 + 'a');
    }

    *ptr = '\0';

    // Reverse the string
    while (ptr1 < ptr) {
        tmp_char = *--ptr;
        *ptr = *ptr1;
        *ptr1++ = tmp_char;
    }
}

/** fb_write_number:
 * Writes an integer as a string to the framebuffer at the current cursor position.
 *
 * @param num The number to write
 */
void fb_write_number(int num) {
    char buffer[12]; // Enough to hold a 32-bit integer
    itoa(num, buffer, 10); // Convert integer to string
    fb_write_string(buffer);
}

/** fb_clear:
 * Clears the framebuffer and resets the cursor to (0, 0).
 */
void fb_clear() {
    for (unsigned int i = 0; i < FB_ROWS * FB_COLS; i++) {
        fb_write_cell(i, ' ', foreground_color, background_color);
    }
    cursor_x = 0;
    cursor_y = 0;
    fb_move(0, 0);
}
