#include "wram.h"

static uint8_t gb_hram0[0x1000]; // Address: 0xC000-0xCFFF
static uint8_t gb_hram1[0x1000]; // Address: 0xD000-0xDFFF / Switchable bank 1-7 in CGB mode

uint8_t wram_read(uint16_t addr) {
    if (BETWEEN(addr, 0xC000, 0xCFFF)) {
        return gb_hram0[addr - BASE_ADDRESS_WRAM0];
    }
    if (BETWEEN(addr, 0xD000, 0xDFFF)) {
        return gb_hram1[addr - BASE_ADDRESS_WRAM1];
    }
}

void wram_write(uint16_t addr, uint8_t data) {
    if (BETWEEN(addr, 0xC000, 0xCFFF)) {
        gb_hram0[addr - BASE_ADDRESS_WRAM0] = data;
    }
    if (BETWEEN(addr, 0xD000, 0xDFFF)) {
        gb_hram1[addr - BASE_ADDRESS_WRAM1] = data;
    }
    return;
}