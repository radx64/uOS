#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

typedef struct gdt_descriptor
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_descriptor_t;

typedef struct gdt_pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_pointer_t;

void gdt_set(gdt_pointer_t* gdt_ptr);

void gdt_init();

void gdt_set_desc(gdt_descriptor_t* descriptor, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif  // GDT_H_