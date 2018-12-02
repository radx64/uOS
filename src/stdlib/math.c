#include "math.h"

int32_t pow(int32_t base, int32_t power)
{ 
    int32_t i = 0, product = 1;

    for(i = 0; i < power; ++i) {
        product = product * base;
    }

    return product;
}

uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b; 
}

uint32_t min(uint32_t a, uint32_t b)
{
    return (a < b) ? a : b;
}