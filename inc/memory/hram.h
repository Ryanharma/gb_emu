#pragma once

#include "common.h"

#define BASE_ADDRESS_HRAM 0xFF80

uint8_t hram_read(uint16_t addr);
void hram_write(uint16_t addr, uint8_t data);