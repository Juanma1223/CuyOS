#include "random.h"
#include <stdint.h>

// LCG parameters
#define LCG_A 1664525
#define LCG_C 1013904223
#define LCG_M 0xFFFFFFFF

static uint32_t lcg_seed = 1;

// Seed the random number generator
void srand(uint32_t seed) {
    lcg_seed = seed;
}

// Generate a random number
uint32_t rand(void) {
    lcg_seed = (LCG_A * lcg_seed + LCG_C) & LCG_M;
    return lcg_seed;
}
