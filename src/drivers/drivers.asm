global outb     ; make the label outb visible outside this file
; outb - send a byte to an I/O port
outb:
    mov al, [esp + 8]  ; move the byte to write to al register
    mov dx, [esp + 4]  ; move the port addres to dx register
    out dx, al         ; write byte to specific address
    ret

global inb      ; make the label outb visible outside this file
; inb - send a byte to an I/O port
inb:
    mov dx, [esp + 4]  ; move the address of the I/O port to the dx register
    in al, dx          ; read a byte fom the I/O port and store it inr the al reg.         
    ret                ; return the read byte

global keyboard_handler
extern keyboard_handler_main
keyboard_handler:                 
    call    keyboard_handler_main
    iretd