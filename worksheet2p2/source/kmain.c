#include "framebuffer.h"
#include "keyboard.h"
#include "interrupts.h"



#define FB_GREEN 2
#define FB_DARK_GREY 8
#define FB_RED 4
#define FB_BLACK 0

int sum_of_three(int arg1, int arg2, int arg3);

int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

void kmain() {
    // Install the Interrupt Descriptor Table (IDT)
    interrupts_install_idt();

    // Clear the screen
    fb_clear();

    // Set initial text color
    fb_set_color(FB_GREEN, FB_BLACK);

    // Start a message
    fb_write_string("Type below:\n");

    // Initialize cursor position
    fb_move(0, 2);

    // Infinite loop to handle typing
    // while (1) {
    //     u8int scan_code = keyboard_read_scan_code();
    //     u8int ascii = keyboard_scan_code_to_ascii(scan_code);

    //     if (ascii) {
    //         unsigned short cursor_x = fb_get_cursor_x();
    //         unsigned short cursor_y = fb_get_cursor_y();

    //         if (ascii == '\b') {
    //             // Handle backspace
    //             if (cursor_x > 0) {
    //                 cursor_x--;
    //             } else if (cursor_y > 0) {
    //                 cursor_y--;
    //                 cursor_x = FB_COLS - 1;
    //             }
            //     fb_write_cell(cursor_x + cursor_y * FB_COLS, ' ', FB_GREEN, FB_BLACK);
            // } else if (ascii == '\n') {
            //     // Handle Enter
            //     cursor_x = 0;
            //     cursor_y++;
            // } else {
            //     // Handle regular characters
            //     fb_write_cell(cursor_x + cursor_y * FB_COLS, ascii, FB_GREEN, FB_BLACK);
            //     cursor_x++;
            //     if (cursor_x >= FB_COLS) {
            //         cursor_x = 0;
            //         cursor_y++;
            //     }
            // }

            // // Update cursor position
            // if (cursor_y >= FB_ROWS) {
            //     cursor_y = 2; // Reset to row 2
            // }
            // fb_move(cursor_x, cursor_y);
       // }
    //}
}