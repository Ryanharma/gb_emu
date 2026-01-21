#include "bus.h"

/*
    Start	End	    Description                         Notes
    0000	3FFF	16 KiB ROM bank 00	                From cartridge, usually a fixed bank
    4000	7FFF	16 KiB ROM Bank 01~NN	            From cartridge, switchable bank via mapper (if any)
    8000	9FFF	8 KiB Video RAM (VRAM)	            In CGB mode, switchable bank 0/1
    A000	BFFF	8 KiB External RAM                  From cartridge, switchable bank if any
    C000	CFFF	4 KiB Work RAM (WRAM)	
    D000	DFFF	4 KiB Work RAM (WRAM)	            In CGB mode, switchable bank 1~7
    E000	FDFF	Mirror of C000~DDFF (ECHO RAM)	    Nintendo says use of this area is prohibited.
    FE00	FE9F	Object attribute memory (OAM)	
    FEA0	FEFF	Not Usable                          Nintendo says use of this area is prohibited
    FF00	FF7F	I/O Registers	
    FF80	FFFE	High RAM (HRAM)	
    FFFF	FFFF	Interrupt Enable register (IE)	
*/

uint8_t bus_read(uint16_t addr, cart_t *cart) {
    if (BETWEEN(addr, 0x0000, 0x7FFF)) {
        printf("ROM value at addr 0x%2.2X = 0x%2.2X\n", addr, *(cart->rom_data + addr));
        return *(cart->rom_data + addr);
    }
    if (BETWEEN(addr, 0x8000, 0x9FFF)) {
        ERROR("NOT IMPLEMENTED YET");
    }
}

void bus_write(uint16_t addr, uint8_t data, cart_t *cart) {
    if (BETWEEN(addr, 0x0000, 0x7FFf)) {
        ERROR("NOT ALLOWED TO WRITE ON CARTRIDGE ROM");
    }
}