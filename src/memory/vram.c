#include "vram.h"

static uint8_t gb_vram[0x2000]; // Address: 0x8000-0x9FFF

uint8_t vram_read(uint16_t addr) {
    return gb_vram[addr - BASE_ADDRESS_VRAM];
}

void vram_write(uint16_t addr, uint8_t data) {
    gb_vram[addr - BASE_ADDRESS_VRAM] = data;
    return;
}