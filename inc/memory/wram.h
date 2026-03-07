#pragma once

#include "common.h"

#define BASE_ADDRESS_WRAM0 0xC000
#define BASE_ADDRESS_WRAM1 0xD000

uint8_t wram_read(uint16_t addr);
void wram_write(uint16_t addr, uint8_t data);