#include "math.h"

int32_t pow(int base, int power)
{ 
    int i = 0, product = 1;

    for(i = 0; i < power; ++i) {
        product = product * base;
    }

    return product;
}