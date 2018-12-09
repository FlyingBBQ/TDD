#include "bootloader.h"
#include <stdio.h>

int read_last_bootcode(void)
{
    return BOOT_HOI;
}

int bootloader(void)
{
    return BOOT_SUCCESS;
}
