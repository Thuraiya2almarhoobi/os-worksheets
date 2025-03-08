%include "asm_io.inc"      ; Include assembly I/O 

section .data
    integer1 dd 20         ; Define the first integer (20)
    integer2 dd 8          ; Define the second integer (8)

section .bss
    result resd 1          ; Reserve space for the result

section .text
    global asm_main        ; Declare asm_main as the entry point and make it global

asm_main:
    pusha                  ; Save all general-purpose registers

    mov eax, [integer1]    ; Load integer1 into eax
    add eax, [integer2]    ; Add integer2 to eax (eax = integer1 + integer2)
    mov [result], eax      ; Store the result in 'result' variable

    mov eax, [result]      ; Reload the result into eax for printing
    call print_int         ; Print the result using print_int function
    call print_nl          ; Print a newline to clean up output

    popa                   ; Restore all general-purpose registers
    mov eax, 0             ; Set return value to 0
    ret                    ; Return to the calling function (driver.c)
