#ifndef INCLUDE_INTERRUPTS
#define INCLUDE_INTERRUPTS

#include "types.h"

struct IDT {
    u16int size;
    u32int address;
} __attribute__((packed));

struct IDTDescriptor {
    u16int offset_low;         // Offset bits 0..15
    u16int segment_selector;   // Code segment selector in GDT or LDT
    u8int reserved;            // Reserved, always 0
    u8int type_and_attr;       // Type and attributes
    u16int offset_high;        // Offset bits 16..31
} __attribute__((packed));

struct cpu_state {
    u32int eax, ebx, ecx, edx, ebp, esi, edi;
} __attribute__((packed));

struct stack_state {
    u32int error_code;
    u32int eip;
    u32int cs;
    u32int eflags;
} __attribute__((packed));

void interrupt_handler(struct cpu_state cpu, u32int interrupt, struct stack_state stack);
void interrupts_install_idt();
void load_idt(u32int idt_address);
void interrupt_handler_33();
void interrupt_handler_14();

#endif /* INCLUDE_INTERRUPTS */
