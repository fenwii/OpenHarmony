#include <stdlib.h>
#include <stdint.h>

static uint64_t seed;

void srand(unsigned s)
{
    return srandom(seed);
}

int rand(void)
{
   return random();
}
