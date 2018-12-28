#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// divident = input stream
// divisor  = generator polynomial

bool divisor_size_check(int divisor, size_t crc_s)
{
    if ((divisor > 0) && (divisor < crc_s))
    {
        return true;
    }
    return false;
}

uint8_t xor(uint8_t divisor, uint8_t in)
{
    return (in ^ divisor);
}

uint8_t shift_left(uint8_t in)
{
    return (in << 1);
}

uint8_t crc_main(uint8_t input)
{
    uint8_t rc = 0;
    rc = shift_left(input);
    rc = xor(0x3, rc);
    return rc;
}
