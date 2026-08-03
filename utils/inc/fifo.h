/*
Implementation of Pixel FIFO for GB's PPU.
*/

#pragma once
#include "log.h"
#include "common.h"

#define FIFO_SIZE 8

typedef struct {
    // Pixel = 0bmsb_lsb
    bool msb;
    bool lsb;
} pixel_t;

typedef struct {
    // FIFO structure (can contain 8 pixels)
    pixel_t fifo_mem[FIFO_SIZE];
    uint8_t fifo_ptr;
} fifo_t;

bool is_empty(fifo_t *fifo);
bool is_full(fifo_t *fifo);
void push(fifo_t *fifo, pixel_t pixel);
pixel_t pop(fifo_t *fifo);
void clear_fifo(fifo_t *fifo);