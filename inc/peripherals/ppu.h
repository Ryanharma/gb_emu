#pragma once

#include "common.h"
#include "fifo.h"

typedef enum {
    MODE0, // HBlank
    MODE1, // VBlank
    MODE2, // OAM Scan
    MODE3, // Pixel rendering
} ppu_mode_t;

typedef struct {
    fifo_t bg_fifo; // FIFO for background pixels
    fifo_t obj_fifo; // FIFO for objects on the screen
    ppu_mode_t mode;
} ppu_t;

extern ppu_t gb_ppu;

void pixel_fetcher();
void ppu_step(); // PPU individual dot