#include "framebuffer.h"

#define FB_GREEN 2
#define FB_DARK_GREY 8
#define FB_RED 4
#define FB_BLACK 0

int sum_of_three(int arg1, int arg2, int arg3);

int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

void kmain() {
    // Clear the screen at the start
    fb_clear();

    // Write 'A' directly at position (0, 0)
    fb_write_cell(0, 'A', FB_GREEN, FB_BLACK);

    // Move the cursor after 'A' and set text color
    fb_move(0, 1);  // Move to second cell
    fb_set_color(FB_GREEN, FB_DARK_GREY);

    // Write a message to the framebuffer
    fb_write_string("Hello, World!\n");

    // Call sum_of_three and store the result
    int result = sum_of_three(1, 2, 3);

    // Write the result of sum_of_three to the framebuffer
    fb_write_string("The result of sum_of_three is: ");
    fb_write_number(result);  // Write the number (6)
    fb_write_string("\n");

    // Change color to red text on black background
    fb_set_color(FB_RED, FB_BLACK);
    fb_write_string("This is red text.\n");

    // Move the cursor to position (10, 10) and write a custom message
    fb_move(10, 10);
    fb_write_string("Custom position!");

    // Return cursor to the first row, second cell (after 'A')
    fb_move(0, 1);
}

