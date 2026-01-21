#pragma once

#include "common.h"

typedef struct {
    uint8_t entry[4]; // 4 memory addresses
    uint8_t logo[0x30];
    char title[0xF];

    uint8_t cgb_flag; // Decide whether to enable color mode or to stay in monochrome mode
    uint16_t new_lic_code; // Contains two ascii characters representing licence code
    uint8_t sgb_flag; // Specifies if the game support SGB functions (super game boy)
    uint8_t cart_type; // What kind of hw is present on the cartridge (RAM/MBC1/Battery)
    uint8_t rom_size; // How much ROM in the cartridge
    uint8_t ram_size; // How much RAM in the cartridge
    uint8_t dest_code; // Japan or overseas?
    uint8_t old_lic_code;
    uint8_t version;
} cart_header_t;

typedef struct {
    cart_header_t *header;
    char filename[1024];
    uint32_t rom_size;
    uint8_t *rom_data;
} cart_t;

bool cart_load(char *cart_path, cart_t *cart);