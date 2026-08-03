#pragma once

#include "common.h"

#define BASE_ADDRESS_OAM 0xFE00

uint8_t oam_read(uint16_t addr);
void oam_write(uint16_t addr, uint8_t data);
