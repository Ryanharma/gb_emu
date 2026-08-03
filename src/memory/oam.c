#include "oam.h"

static uint8_t gb_oam[0xA0]; // Address: 0xFE00-0xFE9F

uint8_t oam_read(uint16_t addr) {
    return gb_oam[addr - BASE_ADDRESS_OAM];
}

void oam_write(uint16_t addr, uint8_t data) {
    gb_oam[addr - BASE_ADDRESS_OAM] = data;
    return;
}