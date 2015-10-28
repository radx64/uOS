#include "string.h"

#include "math.h"

unsigned int strlen(const char* s)
{
    unsigned int len = 0;
    while(s[len] != '\0')
    {
        ++len;
    }
    return len;
}

int strcmp(const char* s1, const char* s2)
{
	while (*s1 == *s2++)
	{
		if(*s1++ == 0)
		{
			return 0;
		}
	}

	return (*(const unsigned char*)s1 - *(const unsigned char*)(s2-1));
}

char* strcpy(char *dest, const char *src)
{
    char *str = dest;
    while (*src)
    {
        *dest++ = *src++;
    }
    *dest = '\0';
    return str;
}

int32_t atoi(char *p)
{
    int k = 0, sign = 1;

    if (p[0] == '-') 
    {
        sign = -1;
        p++;
    } 
    else if (p[0] == '+') 
    {
        sign = 1;
        p++;
    }
    while (*p) 
    {
        if ( (int)(*p) >= 48 && (int)(*p) <= 57) 
        {
            k = (k<<3)+(k<<1)+(*p)-'0';
            p++;
        } 
        else 
        {
            return 0;
        }

    }
    return k*sign;
}

int32_t oct_to_dec(int n) 
{
    int dec = 0, i = 0, rem; 
 
    while (n != 0) 
    { 
        rem = n % 10; 
        n /= 10; 
        dec += rem * pow(8, i);
        ++i;
    }
    return dec;
}

char *itoa(uint64_t val, char *str, int32_t base)
{
    *str = '\0'; // Currently pointing to the end of string
    if (val == 0) 
    {
        *--str = '0';
        return str;
    }
    if (base != 10 && base != 16) 
    {
        return str;
    }
    while (val) {
        *--str = "0123456789abcdef"[val%base];
        val = val/base;
    }
    return str;
}

void *memset(void *ptr, uint8_t value, uint64_t num)
{
    uint8_t *temp = (uint8_t *)ptr;

    while(num--) {
        *temp++ = value; 
    }
    return ptr;
}

void *memcpy(void *destination, void *source, uint64_t num) 
{
    uint8_t *dest = (uint8_t *)destination;
    uint8_t *src = (uint8_t *)source;

    while(num--) {
        *dest++ = *src++; 
    }

    return destination;
}