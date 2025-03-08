%include "asm_io.inc"      ; Include assembly I/O 

section .data
    welcome_msg db 'Welcome to the program!', 0
    too_small_msg db 'Error: The number is too small.', 0
    too_big_msg db 'Error: The number is too big.', 0
    ask_name_msg db 'Please enter your name: ', 0
    ask_count_msg db 'Please enter the number of times to print the welcome message: ', 0
    newline db 0xA, 0
    welcome_format db 'Welcome, ', 0

section .bss
    name resb 50              ; Buffer for name input
    count resd 1

section .text
    global asm_main           ; Entry point for the program

asm_main:
    pusha
    ; Display welcome message and ask for the user's name
    mov eax, welcome_msg
    call print_string
    mov eax, ask_name_msg
    call print_string

    ; Read the user's name
    mov eax, name
    call read_name

    ; Ask for the number of times to print the welcome message
    mov eax, ask_count_msg
    call print_string
    call read_int
    mov [count], eax         ; Store the count

    ; Validate if the count is within range (50 to 100)
    mov eax, [count]
    cmp eax, 50
    jl print_too_small       ; If count < 50, jump to print_too_small
    cmp eax, 100
    jg print_too_big         ; If count > 100, jump to print_too_big

    ; Print "Welcome, [name]" `count` times
print_welcome_loop:
    mov eax, welcome_format
    call print_string        ; Print "Welcome, "
    mov eax, name
    call print_string        ; Print the user's name
    mov eax, newline
    call print_string        ; Print a newline

    dec dword [count]        ; Decrease count
    cmp dword [count], 0
    jg print_welcome_loop    ; Loop if count > 0

    jmp Exit_program         ; Exit the program

print_too_small:
    mov eax, too_small_msg
    call print_string
    mov eax, newline
    call print_string
    jmp Exit_program         ; Exit the program

print_too_big:
    mov eax, too_big_msg
    call print_string
    mov eax, newline
    call print_string
    jmp Exit_program         ; Exit the program

Exit_program:
    popa
    mov eax, 0               ; syscalls: exit
    ret

read_name:
    pusha
    mov ecx, 0
read_loop:
    call read_char
    cmp al, 0xA              ; Check for newline
    je done_reading
    mov [name + ecx], al
    inc ecx
    jmp read_loop
done_reading:
    mov byte [name + ecx], 0
    popa
    ret
