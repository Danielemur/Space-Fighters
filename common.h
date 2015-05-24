#pragma once

#include <stdint.h>

uint32_t jenkins(uint32_t a, uint32_t b, uint32_t c);

vfloat jenkinsf(uint32_t a, uint32_t b, uint32_t c);
    
uint64_t xorshift(uint64_t *state);

vfloat xorshiftf(uint64_t *state);
