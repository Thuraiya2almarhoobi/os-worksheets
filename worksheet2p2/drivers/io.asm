global outb
global inb

section .text

; outb - Sends a byte to the specified I/O port
; Parameters:
;   [esp+4] -> The I/O port (dx)
;   [esp+8] -> The data to send (al)
outb:
    mov al, [esp + 8]    ; Load the data to send into AL
    mov dx, [esp + 4]    ; Load the port into DX
    out dx, al           ; Output the byte to the port
    ret

; inb - Reads a byte from the specified I/O port
; Parameters:
;   [esp+4] -> The I/O port (dx)
; Returns:
;   AL -> The byte read from the port
inb:
    mov dx, [esp + 4]    ; Load the port into DX
    in al, dx            ; Input the byte from the port into AL
    movzx eax, al        ; Zero-extend AL into EAX
    ret
