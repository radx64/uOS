#ifndef STRING_H
#define STRING_H

#include "stdint.h"

unsigned int strlen(const char* s);

int strcmp(const char* s1, const char* s2);

char* strcpy(char *dest, const char *src);

int32_t atoi(char *p);

int32_t oct_to_dec(int n);

char *itoa(uint64_t val, char *str, int32_t base);

void *memset(void *ptr, uint8_t value, uint64_t num);

void *memcpy(void *destination, void *source, uint64_t num);

#endif // STRING_H