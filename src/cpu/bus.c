#include "bus.h"
#include "vram.h"
#include "wram.h"
#include "hram.h"
#include "io.h"

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
        // Read into cartridge ROM
        return *(cart->rom_data + addr);
    }

    if (BETWEEN(addr, 0x8000, 0x9FFF)) {
        // Read VRAM
        vram_read(addr);
    }

    if (BETWEEN(addr, 0xA000, 0xBFFF)) {
        // Read External RAM (from cartridge, for game with saves)
        ERROR("NOT IMPLEMENTED YET");
    }

    if (BETWEEN(addr, 0xC000, 0xDFFF)) {
        // Read Work RAM
        wram_read(addr);
    }

    if (BETWEEN(addr, 0xE000, 0xFDFF)) {
        // Echo RAM
        ERROR("Use of this area is prohibited");
    }
    
    if (BETWEEN(addr, 0xFE00, 0xFE9F)) {
        // Read OAM (Object Attribute Memory)
        ERROR("NOT IMPLEMENTED YET");
    }

    if (BETWEEN(addr, 0xFEA0, 0xFEFF)) {
        ERROR("Not usable");
    }

    if (BETWEEN(addr, 0xFF00, 0xFF7F) || addr == 0xFFFF) {
        // Read I/O registers / peripherals functionalities
        io_read(addr);
    }
    
    if (BETWEEN(addr, 0xFF80, 0xFFFE)) {
        // Read HRAM
        hram_read(addr);
    }
}

void bus_write(uint16_t addr, uint8_t data, cart_t *cart) {
    if (BETWEEN(addr, 0x0000, 0x7FFF)) {
        ERROR("NOT ALLOWED TO WRITE ON CARTRIDGE ROM");
    }

    if (BETWEEN(addr, 0x8000, 0x9FFF)) {
        // Write VRAM
        vram_write(addr, data);
    }

    if (BETWEEN(addr, 0xA000, 0xBFFF)) {
        // Write External RAM (from cartridge, for save purpose?)
        ERROR("NOT IMPLEMENTED YET");
    }

    if (BETWEEN(addr, 0xC000, 0xDFFF)) {
        // Write Work RAM
        wram_write(addr, data);
    }

    if (BETWEEN(addr, 0xE000, 0xFDFF)) {
        // Echo RAM
        ERROR("Use of this area is prohibited");
    }
    
    if (BETWEEN(addr, 0xFE00, 0xFE9F)) {
        // Write OAM (Object Attribute Memory)
        ERROR("NOT IMPLEMENTED YET");
    }

    if (BETWEEN(addr, 0xFEA0, 0xFEFF)) {
        ERROR("Not usable");
    }

    if (BETWEEN(addr, 0xFF00, 0xFF7F) || addr == 0xFFFF) {
        // Write I/O registers
        io_write(addr, data);
    }
    
    if (BETWEEN(addr, 0xFF80, 0xFFFE)) {
        // Write HRAM
        hram_write(addr, data);
    }
}