#include "interrupts.h"
#include "pic.h"
#include "io.h"
#include "framebuffer.h"
#include "keyboard.h"

#define INTERRUPTS_DESCRIPTOR_COUNT 256
#define INTERRUPTS_KEYBOARD 33
#define INPUT_BUFFER_SIZE 256

struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;

void interrupts_init_descriptor(s32int index, u32int address) {
    idt_descriptors[index].offset_low = (address & 0xFFFF);          // Offset bits 0..15
    idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF;  // Offset bits 16..31
    idt_descriptors[index].segment_selector = 0x08;                 // Code segment selector in GDT
    idt_descriptors[index].reserved = 0x00;                         // Reserved, always 0
    idt_descriptors[index].type_and_attr = 0x8E;                    // Present, Ring 0, 32-bit interrupt gate
}

void interrupts_install_idt() {
    // Initialize keyboard interrupt (IRQ1)
    interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (u32int) interrupt_handler_33);

    // Set IDT size and address
    idt.address = (u32int) &idt_descriptors;
    idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT - 1;

    // Load the IDT
    load_idt((u32int) &idt);

    // Remap PIC interrupts to avoid conflicts
    pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);

    // Unmask IRQ1 (keyboard interrupt)
    outb(0x21, inb(0x21) & ~(1 << 1));
}

void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, u32int interrupt, __attribute__((unused)) struct stack_state stack) {
    u8int input;
    u8int ascii;
    static unsigned short cursor_x = 0;  // Track cursor X position
    static unsigned short cursor_y = 15; // Start at row 15 for keyboard input

    switch (interrupt) {
        case INTERRUPTS_KEYBOARD:
            // Check if a keyboard event occurred
            while (inb(0x64) & 1) {
                input = keyboard_read_scan_code(); // Read scan code from the keyboard

                // Ignore break codes (key releases) and special 0xFE code
                if (input == 0xFE || (input & 0x80)) {
                    continue;
                }

                // Convert scan code to ASCII
                ascii = keyboard_scan_code_to_ascii(input);

                if (ascii != 0) {
                    if (ascii == '\b') { // Handle backspace
                        if (cursor_x > 0) {
                            cursor_x--;
                        } else if (cursor_y > 0) {
                            cursor_y--;
                            cursor_x = FB_COLS - 1;
                        }
                        unsigned int pos = cursor_y * FB_COLS + cursor_x;
                        fb_write_cell(pos, ' ', FB_GREEN, FB_BLACK); // Clear the character
                        fb_move(cursor_x, cursor_y);
                    } else if (ascii == '\n') { // Handle newline
                        cursor_x = 0;
                        cursor_y++;
                        if (cursor_y >= FB_ROWS) {
                            cursor_y = 15; // Wrap back to start row
                        }
                        fb_move(cursor_x, cursor_y);
                    } else { // Handle regular characters
                        fb_write_cell(cursor_x + cursor_y * FB_COLS, ascii, FB_GREEN, FB_BLACK);
                        cursor_x++;
                        if (cursor_x >= FB_COLS) {
                            cursor_x = 0;
                            cursor_y++;
                            if (cursor_y >= FB_ROWS) {
                                cursor_y = 15; // Wrap back to start row
                            }
                        }
                        fb_move(cursor_x, cursor_y);
                    }
                }
            }

            // Acknowledge interrupt to the PIC
            pic_acknowledge(interrupt);
            break;

        default:
            break;
    }
}
