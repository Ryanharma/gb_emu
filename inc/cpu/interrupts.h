#pragma once

#include "common.h"
#include "cpu.h"
#include "bus.h"
#include "cart.h"

typedef struct {
    uint8_t IF; // Address 0xFFFF
    uint8_t IE; // Address 0xFF0F
} gb_interrupt_t;

extern gb_interrupt_t gb_interrupts; // Registered value

void interrupt_request(cpu_t *cpu, cart_t *cart, gb_interrupt_t *gb_interrupt);
void interrupt_handle(cpu_t *cpu, cart_t *cart, gb_interrupt_t *gb_interrupt);