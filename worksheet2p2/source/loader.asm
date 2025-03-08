global loader
extern sum_of_three
extern fb_write_cell  ; Declare the framebuffer write function
extern kmain          ; Declare the main kernel function

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE  ; Reserve stack space (4 KB)

section .text
align 4
dd MAGIC_NUMBER
dd FLAGS
dd CHECKSUM

loader:
    ; Initialize the stack pointer
    mov esp, kernel_stack + KERNEL_STACK_SIZE  ; Point to the top of the stack

    ; Debug: Write 0xCAFEBABE to eax
    mov eax, 0xCAFEBABE

    ; Call the C function sum_of_three
    push dword 3       ; Push third argument
    push dword 2       ; Push second argument
    push dword 1       ; Push first argument
    call sum_of_three  ; Call the C function
    add esp, 12        ; Clean up the stack (3 arguments * 4 bytes)

    ; Write 'A' to the framebuffer with green foreground and dark grey background
    push dword 8       ; Push background color (dark grey)
    push dword 2       ; Push foreground color (green)
    push dword 'A'     ; Push character 'A'
    push dword 0       ; Push position 0 (row 0, column 0)
    call fb_write_cell ; Call framebuffer write function
    add esp, 16        ; Clean up the stack (4 arguments * 4 bytes)

    ; Call the C kernel main function (kmain)
    call kmain

.loop:
    jmp .loop          ; Infinite loop
