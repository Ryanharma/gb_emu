#include "lcd.h"

lcd_t gb_lcd = {0};

uint8_t lcd_read(lcd_t *lcd_ctx, uint16_t addr) {
    switch (addr) {
        case (0xFF40): {
            return lcd_ctx->LCDC;
        }
        case (0xFF41): {
            return lcd_ctx->STAT;
        }
        case (0xFF42): {
            return lcd_ctx->SCY;
        }
        case (0xFF43): {
            return lcd_ctx->SCX;
        }
        case (0xFF44): {
            return lcd_ctx->LY;
        }
        case (0xFF45): {
            return lcd_ctx->LYC;
        }
        case (0xFF46): {
            return lcd_ctx->DMA;
        }
        case (0xFF47): {
            return lcd_ctx->BGP;
        }
        case (0xFF48): {
            return lcd_ctx->OBP0;
        }
        case (0xFF49): {
            return lcd_ctx->OBP1;
        }
        case (0xFF4A): {
            return lcd_ctx->WY;
        }
        case (0xFF4B): {
            return lcd_ctx->WX;
        }
        default: {
            ERROR("Error: Undefined address for LCD subsystem");
        }
    }
}

void lcd_write(lcd_t *lcd_ctx, uint16_t addr, uint8_t value) {
    switch (addr) {
        case (0xFF40): {
            lcd_ctx->LCDC = value;
            break;
        }
        case (0xFF41): {
            lcd_ctx->STAT = value;
            break;
        }
        case (0xFF42): {
            lcd_ctx->SCY = value;
            break;
        }
        case (0xFF43): {
            lcd_ctx->SCX = value;
            break;
        }
        case (0xFF44): {
            lcd_ctx->LY = value;
            break;
        }
        case (0xFF45): {
            lcd_ctx->LYC = value;
            break;
        }
        case (0xFF46): {
            lcd_ctx->DMA = value;
            break;
        }
        case (0xFF47): {
            lcd_ctx->BGP = value;
            break;
        }
        case (0xFF48): {
            lcd_ctx->OBP0 = value;
            break;
        }
        case (0xFF49): {
            lcd_ctx->OBP1 = value;
            break;
        }
        case (0xFF4A): {
            lcd_ctx->WY = value;
            break;
        }
        case (0xFF4B): {
            lcd_ctx->WX = value;
            break;
        }
        default: {
            ERROR("Error: Undefined address for LCD subsystem");
        }
    }
    return;
}