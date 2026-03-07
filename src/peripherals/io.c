#include "io.h"
#include "lcd.h"
#include "timer.h"
#include "interrupts.h"

uint8_t io_read(uint16_t addr) {
    if (BETWEEN(addr, 0xFF04, 0xFF07)) {
        return timer_read(&gb_timer, addr);
    }
    if (addr == 0xFF0F) {
        return gb_interrupt.IF;
    }
    if (BETWEEN(addr, 0xFF40, 0xFF4B)) {
        return lcd_read(&gb_lcd, addr);
    }
    if (addr == 0xFFFF) {
        return gb_interrupt.IE;
    }
}

void io_write(uint16_t addr, uint8_t data) {
    if (BETWEEN(addr, 0xFF04, 0xFF07)) {
        timer_write(&gb_timer, addr, data);
    }
    if (addr == 0xFF0F) {
        gb_interrupt.IF = data;
    }
    if (BETWEEN(addr, 0xFF40, 0xFF4B)) {
        lcd_write(&gb_lcd, addr, data);
    }
    if (addr == 0xFFFF) {
        gb_interrupt.IE = data;
    }
    return;
}