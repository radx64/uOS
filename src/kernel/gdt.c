#include "gdt.h"

#include "drivers/serial.h"

#define GDT_LEN 5

static gdt_descriptor_t gdt[GDT_LEN];
static gdt_pointer_t gdt_ptr;

void gdt_init()
{
	serial_write("gdt_init....");
	gdt_set_desc(&gdt[0], 0, 0, 0, 0);
	gdt_set_desc(&gdt[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_desc(&gdt[2], 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_desc(&gdt[3], 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_desc(&gdt[4], 0, 0xFFFFFFFF, 0xF2, 0xCF);

	gdt_ptr.base = (uint32_t) &gdt;
	gdt_ptr.limit = sizeof(gdt_descriptor_t) * GDT_LEN - 1;

	gdt_set(&gdt_ptr);
	serial_write("[ OK ]\r\n");
}

void gdt_set_desc(gdt_descriptor_t* descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	descriptor->base_low    		= (base & 0xFFFF);
	descriptor->base_middle 		= (base >> 16) & 0xFF;
	descriptor->base_high   		= (base >> 24) & 0xFF;
	descriptor->limit_low   		= (limit & 0xFFFF);
	descriptor->granularity 		= ((limit >> 16) & 0x0F) | (granularity & 0xF0);
	descriptor->access = access;
}