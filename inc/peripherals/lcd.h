#pragma once

#include "common.h"

typedef struct {
    // Defines LCD control/status registers
    uint8_t LCDC; // Address FF40, LCD control reg 
    uint8_t STAT; // Address FF41, LCD status
    uint8_t SCY; // Address FF42, Background viewport Y position
    uint8_t SCX; // Address FF43, Background viewport X position
    uint8_t LY; // Address FF44, LCD Y coordinate (read only)
    uint8_t LYC; // Address FF45, Compare LY and LYC to set interrupt in STAT reg
    uint8_t DMA; // Address FF46, for DMA transfer
    uint8_t BGP; // Address FF47, color palette (Non CGB mode only)
    uint8_t OBP0; // Address FF48, (Non CGB mode only)
    uint8_t OBP1; // Address FF49, (Non CGB mode only)
    uint8_t WY; // Address FF4A, Window Y postion
    uint8_t WX; // Address FF4B, Window X position + 7
} lcd_t;

extern lcd_t gb_lcd;
uint8_t lcd_read(lcd_t *lcd_ctx, uint16_t addr);
void lcd_write(lcd_t *lcd_ctx, uint16_t addr, uint8_t value);