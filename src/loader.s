global loader                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)

KERNEL_STACK_SIZE equ 4096      ; size of a stack in bytes

section .text                   ; start of the text (code) section
align 4                         ; code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; same with the flags
    dd CHECKSUM                 ; as well as the checksum

loader:                         				; the loader label (defined as entry point in linking script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE 	; point esp to start of the stack (end of memory area)

extern kmain                    ; declare kmain as external function
    call kmain                  ; call main function

.loop:
;	cli							; disable interrupts
	hlt							; halt cpu
     jmp .loop                  ; loop forever (should be never called)

section .bss
align 4                         ; align to 4 bytes
kernel_stack:                   ; label pointing to begining of memory
    resb KERNEL_STACK_SIZE      ; reserve stack for the kernel of size KERNEL_STACK_SIZE
