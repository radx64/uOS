#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "drivers/io.h"
#include "drivers/serial.h"

#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define INTERRUPT_GATE 0x8e
#define IDT_SIZE 256

#include "idt.h"

struct IDT_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

extern void load_idt(unsigned long *idt_ptr);

struct IDT_entry IDT[IDT_SIZE];

void idt_set_gate(uint8_t index, uint32_t base, uint16_t selector, uint8_t flags)
{
   IDT[index].offset_lowerbits = base & 0xFFFF;
   IDT[index].offset_higherbits = (base >> 16) & 0xFFFF;
   IDT[index].selector     = selector;
   IDT[index].zero = 0;
   // Must uncomment the OR below when will start implementing and using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   IDT[index].type_attr   = flags /* | 0x60 */;}

void idt_init(void* keyboard_handler)
{
    serial_write("idt_init....");
    unsigned long keyboard_address;
    keyboard_address = (unsigned long) keyboard_handler;

    /* populate IDT entry for interrupts 0-31 */
    idt_set_gate( 0, (uint32_t) isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uint32_t) isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uint32_t) isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (uint32_t) isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (uint32_t) isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (uint32_t) isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (uint32_t) isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (uint32_t) isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (uint32_t) isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (uint32_t) isr9 , 0x08, 0x8E);
    idt_set_gate( 10, (uint32_t) isr10 , 0x08, 0x8E);
    idt_set_gate( 11, (uint32_t) isr11 , 0x08, 0x8E);
    idt_set_gate( 12, (uint32_t) isr12 , 0x08, 0x8E);
    idt_set_gate( 13, (uint32_t) isr13 , 0x08, 0x8E);
    idt_set_gate( 14, (uint32_t) isr14 , 0x08, 0x8E);
    idt_set_gate( 15, (uint32_t) isr15 , 0x08, 0x8E);
    idt_set_gate( 16, (uint32_t) isr16 , 0x08, 0x8E);
    idt_set_gate( 17, (uint32_t) isr17 , 0x08, 0x8E);
    idt_set_gate( 18, (uint32_t) isr18 , 0x08, 0x8E);
    idt_set_gate( 19, (uint32_t) isr19 , 0x08, 0x8E);
    idt_set_gate( 20, (uint32_t) isr20 , 0x08, 0x8E);
    idt_set_gate( 21, (uint32_t) isr21 , 0x08, 0x8E);
    idt_set_gate( 22, (uint32_t) isr22 , 0x08, 0x8E);
    idt_set_gate( 23, (uint32_t) isr23 , 0x08, 0x8E);
    idt_set_gate( 24, (uint32_t) isr24 , 0x08, 0x8E);
    idt_set_gate( 25, (uint32_t) isr25 , 0x08, 0x8E);
    idt_set_gate( 26, (uint32_t) isr26 , 0x08, 0x8E);
    idt_set_gate( 27, (uint32_t) isr27 , 0x08, 0x8E);
    idt_set_gate( 28, (uint32_t) isr28 , 0x08, 0x8E);
    idt_set_gate( 29, (uint32_t) isr29 , 0x08, 0x8E);
    idt_set_gate( 30, (uint32_t) isr30 , 0x08, 0x8E);
    idt_set_gate( 31, (uint32_t) isr31 , 0x08, 0x8E);

    /* populate IDT entry of keyboard's interrupt */
    idt_set_gate(33, keyboard_address, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);

    /*     Ports
    *    PIC1   PIC2
    *Command 0x20   0xA0
    *Data    0x21   0xA1
    */

    /* ICW1 - begin initialization */
    outb(0x20 , 0x11);
    outb(0xA0 , 0x11);

    /* ICW2 - remap offset address of IDT */
    /*
    * In x86 protected mode, we have to remap the PICs beyond 0x20 because
    * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
    */
    outb(0x21 , 0x20);
    outb(0xA1 , 0x28);

    /* ICW3 - setup cascading */
    outb(0x21 , 0x00);
    outb(0xA1 , 0x00);

    /* ICW4 - environment info */
    outb(0x21 , 0x01);
    outb(0xA1 , 0x01);
    /* Initialization finished */

    /* mask interrupts */
    outb(0x21 , 0xff);
    outb(0xA1 , 0xff);

    /* fill the IDT descriptor */
    unsigned long idt_address;
    unsigned long idt_ptr[2];
    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16 ;

    load_idt(idt_ptr);
    serial_write("[ OK ]\r\n");
}

