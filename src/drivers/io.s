global outb 	; make the label outb visible outside this file
; outb - send a byte to an I/O port
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret