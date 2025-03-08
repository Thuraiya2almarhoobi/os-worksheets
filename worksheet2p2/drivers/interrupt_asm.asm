extern interrupt_handler

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push dword 0        ; Push 0 as error code
    push dword %1       ; Push the interrupt number
    jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push dword %1       ; Push the interrupt number
    jmp common_interrupt_handler
%endmacro

common_interrupt_handler:
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp
    call interrupt_handler
    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    add esp, 8  ; Remove error code and interrupt number
    iret


no_error_code_interrupt_handler 33
