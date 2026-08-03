#pragma once

#include "common.h"
#include "instructions.h"

#define BASE_ADDRESS_BOOTROM 0x0000

extern uint8_t BOOT; // Address 0xFF50

uint8_t bootrom_read(uint16_t addr);