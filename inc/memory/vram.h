#pragma once

#include "common.h"

// typedef enum {
//     M8000 = 0,
//     M8800 = 1,
// } am_mode_t;

// typedef struct {
//     uint8_t vram[0x2000]; // Address: 0x8000-0x9FFF
//     am_mode_t am_mode; // Addressing mode for vram
// } vram_t;

// extern vram_t gb_vram;

#define BASE_ADDRESS_VRAM 0x8000

uint8_t vram_read(uint16_t addr);
void vram_write(uint16_t addr, uint8_t data);