#include "gdt.h"

#include "drivers/serial.h"

#define GDT_LEN 5

static gdt_descriptor_t gdt[GDT_LEN];
static gdt_pointer_t gdt_ptr;

/* Initializes GDT */
void gdt_init()
{
	serial_write("gdt_init....");
	gdt_set_desc(&gdt[0], 0x0, 0x00000000, 0x00, 0x00);	// Null segment
	gdt_set_desc(&gdt[1], 0x0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_desc(&gdt[2], 0x0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_desc(&gdt[3], 0x0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_desc(&gdt[4], 0x0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	gdt_ptr.base = (uint32_t) &gdt;
	gdt_ptr.limit = (sizeof(gdt_descriptor_t) * GDT_LEN) - 1;

	gdt_set(&gdt_ptr);
	serial_write("[ OK ]\r\n");
}

/* Sets single GDT entry */
void gdt_set_desc(gdt_descriptor_t* descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	descriptor->base_low    		= (base & 0xFFFF);
	descriptor->base_middle 		= (base >> 16) & 0xFF;
	descriptor->base_high   		= (base >> 24) & 0xFF;
	descriptor->limit_low   		= (limit & 0xFFFF);
	descriptor->granularity 		= ((limit >> 16) & 0x0F) | (granularity & 0xF0);
	descriptor->access              = access;
}