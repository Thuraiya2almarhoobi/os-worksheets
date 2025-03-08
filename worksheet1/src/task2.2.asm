%include "asm_io.inc"      ; Include assembly I/O for printing 

section .data
    result_msg db 'The sum of numbers from 1 to 100 is: ', 0
    range_msg db 'Please enter the range to sum (start end): ', 0
    invalid_range_msg db 'Error: Invalid range. Please enter values between 1 and 100, with start <= end.', 0
    range_sum_msg db 'The sum of numbers in the specified range is: ', 0
    newline db 0xA, 0        ; Newline character

section .bss
    array resd 100           ; Reserve space for an array of 100 integers
    sum resd 1               ; Reserve space for sum
    start resd 1             ; Reserve space for start of range
    end resd 1               ; Reserve space for end of range

section .text
    global asm_main          ; Entry point for the program

asm_main:
    pusha                    ; Save all registers

    ; Initialize the array with values 1 to 100
    mov ecx, 0               ; Counter for array index
initialize_array:
    inc ecx                  ; Increment ECX to get values 1 to 100
    mov [array + (ecx - 1) * 4], ecx  ; Store ECX value at array[ECX - 1]
    cmp ecx, 100             ; Check if ECX reached 100
    jl initialize_array      ; Repeat until ECX > 100

    ; Calculate the sum of the entire array
    mov ecx, 0               ; Reset counter for array index
    mov eax, 0               ; Initialize EAX to accumulate the sum
sum_array:
    add eax, [array + ecx * 4]   ; Add array[ECX] to EAX
    inc ecx                      ; Move to the next element
    cmp ecx, 100                 ; Check if all elements are summed
    jl sum_array                 ; Repeat until ECX = 100

    mov [sum], eax               ; Store the sum result

    ; Output the total sum result
    mov eax, result_msg
    call print_string            ; Print result message
    mov eax, [sum]
    call print_int               ; Print the sum
    mov eax, newline
    call print_string            ; Print a newline

    ; Prompt user for a range to sum
    mov eax, range_msg
    call print_string            ; Print range prompt

    ; Read start of the range
    call read_int
    mov [start], eax             ; Store user input in 'start'

    ; Read end of the range
    call read_int
    mov [end], eax               ; Store user input in 'end'

    ; Validate the range (start >= 1, end <= 100, start <= end)
    mov eax, [start]
    cmp eax, 1
    jl invalid_range             ; If start < 1, go to error message

    mov eax, [end]
    cmp eax, 100
    jg invalid_range             ; If end > 100, go to error message

    mov eax, [start]
    mov ebx, [end]
    cmp eax, ebx
    jg invalid_range             ; If start > end, go to error message

    ; Calculate the sum of the specified range
    mov ecx, [start]
    dec ecx                      ; Adjust for 0-based indexing in array
    mov edx, 0                   ; Initialize EDX to accumulate the sum
range_sum:
    add edx, [array + ecx * 4]   ; Add array[ECX] to EDX
    inc ecx                      ; Move to the next element
    mov ebx, [end]
    dec ebx                      ; Adjust for 0-based indexing in range check
    cmp ecx, ebx                 ; Compare ECX to end value
    jle range_sum                ; Repeat until ECX exceeds end

    ; Output the range sum result
    mov eax, range_sum_msg
    call print_string            ; Print range sum message
    mov eax, edx
    call print_int               ; Print the range sum
    mov eax, newline
    call print_string            ; Print a newline

    jmp Exit_program             ; Exit the program

invalid_range:
    ; Output invalid range error
    mov eax, invalid_range_msg
    call print_string
    mov eax, newline
    call print_string

Exit_program:
    popa                         ; Restore registers
    mov eax, 0                   ; Return 0 to indicate success
    ret
