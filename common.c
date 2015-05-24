#include <stdint.h>
#include <math.h>
#include "common.h"
#include "vec3.h"

uint32_t jenkins(uint32_t a, uint32_t b, uint32_t c)
{
    a = a - b;  a = a - c;  a = a ^ (c >> 13);
    b = b - c;  b = b - a;  b = b ^ (a << 8);
    c = c - a;  c = c - b;  c = c ^ (b >> 13);
    a = a - b;  a = a - c;  a = a ^ (c >> 12);
    b = b - c;  b = b - a;  b = b ^ (a << 16);
    c = c - a;  c = c - b;  c = c ^ (b >> 5);
    a = a - b;  a = a - c;  a = a ^ (c >> 3);
    b = b - c;  b = b - a;  b = b ^ (a << 10);
    c = c - a;  c = c - b;  c = c ^ (b >> 15);
    return c;
}

vfloat jenkinsf(uint32_t a, uint32_t b, uint32_t c)
{
    return jenkins(a, b, c) / (vfloat) UINT32_MAX;
}
 

uint64_t
xorshift(uint64_t *state)
{
    uint64_t x = *state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    *state = x;
    return x * UINT64_C(2685821657736338717);
}

vfloat
xorshiftf(uint64_t *state)
{
    return xorshift(state) / (vfloat)UINT64_MAX;
}
