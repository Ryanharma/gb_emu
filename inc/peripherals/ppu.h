#pragma once

typedef struct {
    bool msb;
    bool lsb;
} pixel_t;

typedef struct {
    pixel_t bg_fifo[16]; // FIFO for background pixels
    pixel_t obj_fifo[16]; // FIFO for objects on the screen
} ppu_t;

extern ppu_t gb_ppu;
