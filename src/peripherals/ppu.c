#include "ppu.h"
#include "vram.h" // Needs access to the VRAM
#include "oam.h" // Needs access to object memory
#include "lcd.h" // To get access to LCD status and control registers

ppu_t gb_ppu = {0};
static uint8_t LX = 0; // X coordinate of current scanline
static uint16_t cur_tilemap = 0x9800; // Current Tile map value
static uint32_t sprite_buf[10]; // Sprite buffer - filled each OAM scan (max 10 per scanline)
static uint8_t cur_index = 0;
static uint16_t scanline_progress = 0; // In dots unit

void pixel_fetcher() {
    // Function that fetches next pixel that needs to be displayed, using current tilemap
    // 2 fetches are needed for 8 pixels since pixels are 2 bits

    // Step 1: determine tilemap to be used based on LCDC bit and coordinnate
    if (BIT(gb_lcd.LCDC, 3) && (gb_lcd.LY < gb_lcd.WY) && (LX < gb_lcd.WX - 7))
        cur_tilemap = 0x9C00;
    if (BIT(gb_lcd.LCDC, 6) && (gb_lcd.LY >= gb_lcd.WY) && (LX >= gb_lcd.WX - 7))
        cur_tilemap = 0x9C00;
    
    // Step 2: compute X and Y coordinate of the window/BG tile to be used
    uint8_t X = 0;
    uint8_t Y = 0;
    bool bit_map = false;
    if ((gb_lcd.LY >= gb_lcd.WY) && (LX >= gb_lcd.WX - 7)) {
        // Current tile is a window tile
        X = LX / 8;
        Y = gb_lcd.WY / 8;
        bit_map = BIT(gb_lcd.LCDC, 6);
    }
    else {
        X = (gb_lcd.SCX/8 + LX / 8) & 0x1F;
        Y = (gb_lcd.SCY + gb_lcd.LY / 8) & 0xFF;
        bit_map = BIT(gb_lcd.LCDC, 3);
    }
    uint16_t tile_map_addr = X | Y << 5 | (bit_map << 10) | (1 << 11) | 9 << 12;
    uint8_t tile_index = vram_read(tile_map_addr);
}

void ppu_step() {
    switch (gb_ppu.mode) {
        case MODE0: {
            // HBlank
            if (scanline_progress >= 456) {
                scanline_progress = 0; // Reset to 0 
                if (gb_lcd.LY >= 144)
                    gb_ppu.mode = MODE1;
                else
                    gb_ppu.mode = MODE2;
            }
            scanline_progress++;
            break;
        }
        case MODE1: {
            // VBlank
            if (gb_lcd.LY >= 154) {
                gb_ppu.mode = MODE2;
            }
            break;
        }
        case MODE2: {
            // OAM Scan -- Scanner toutes les positions de l'OAM pour détecter la présence d'objet
            // ou non sur la ligne en question
            for (int addr = 0xFE00; addr <= 0xFE9F; addr += 4) {
                // Each sprite is 4 bytes long
                int8_t Y_sprite = oam_read(addr);
                int8_t X_sprite = oam_read(addr + 1);
                int8_t tile_index = oam_read(addr + 2);
                int8_t attributes = oam_read(addr + 3);
                if ((X_sprite > 0) && (gb_lcd.LY + 16 >= Y_sprite) && ((gb_lcd.LY + 16 >= Y_sprite + ((gb_lcd.LCDC & (1 << 2)) + 1) * 8)) && cur_index < 10) {
                    int32_t sprite = (Y_sprite << 24) | (X_sprite << 16) | (tile_index << 8) | attributes;
                    sprite_buf[cur_index] = sprite;
                    cur_index++;
                }
            }
            gb_ppu.mode = MODE3;
            scanline_progress += 80;
            break;
        }
        case MODE3: {
            // Drawing pixels to LCD

            // Step 1 : OAM and BG FIFOs are cleared
            clear_fifo(&(gb_ppu.bg_fifo));
            clear_fifo(&(gb_ppu.obj_fifo));

            // Step 2 : Fetch Current Tile data (16 bytes) 
            pixel_fetcher();

            scanline_progress++;
            break;
        }
        default:
            ERROR("UNDEFINED PPU MODE");
    }
    return;
}

void ppu_frame() {
    // Function that renders the whole frame
    return;
}