#pragma once

#include "common.h"
#include "cpu.h"
#include "bus.h"
#include "cart.h"

typedef struct {
    uint8_t IF; // Address 0xFFFF
    uint8_t IE; // Address 0xFF0F
} gb_interrupt_t;

extern gb_interrupt_t gb_interrupt; // Registered value

void interrupt_request(cpu_t *cpu, cart_t *cart, gb_interrupt_t *gb_interrupt);
void interrupt_handle(cpu_t *cpu, cart_t *cart, gb_interrupt_t *gb_interrupt);
// uint8_t interrupt_read(gb_interrupt_t *gb_interrupt, uint16_t address);
// void interrupt_write(gb_interrupt_t *gb_interrupt, uint16_t address, uint8_t value);