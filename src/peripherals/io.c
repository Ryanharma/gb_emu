#include "io.h"
#include "lcd.h"
#include "timer.h"
#include "interrupts.h"
#include "bootrom.h"

uint8_t io_read(uint16_t addr) {
    if (BETWEEN(addr, 0xFF04, 0xFF07)) {
        return timer_read(&gb_timer, addr);
    }
    if (addr == 0xFF0F) {
        return gb_interrupts.IF;
    }
    if (BETWEEN(addr, 0xFF40, 0xFF4B)) {
        return lcd_read(&gb_lcd, addr);
    }
    if (addr == 0XFF50) {
        return BOOT;
    }
    if (addr == 0xFFFF) {
        return gb_interrupts.IE;
    }
}

void io_write(uint16_t addr, uint8_t data) {
    if (BETWEEN(addr, 0xFF04, 0xFF07)) {
        timer_write(&gb_timer, addr, data);
    }
    if (addr == 0xFF0F) {
        gb_interrupts.IF = data;
    }
    if (BETWEEN(addr, 0xFF40, 0xFF4B)) {
        lcd_write(&gb_lcd, addr, data);
    }
    if (addr == 0xFF50)
        BOOT = data;
    if (addr == 0xFFFF) {
        gb_interrupts.IE = data;
    }
    return;
}