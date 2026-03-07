#include "hram.h"

static uint8_t gb_hram[0x7F]; // Address: 0xFF80-0xFFFE / 127 elements (not a power of 2)

uint8_t hram_read(uint16_t addr) {
    return gb_hram[addr - BASE_ADDRESS_HRAM];
}

void hram_write(uint16_t addr, uint8_t data) {
    gb_hram[addr - BASE_ADDRESS_HRAM] = data;
}