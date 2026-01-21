#pragma once

#include "common.h"
#include "cart.h"

uint8_t bus_read(uint16_t addr, cart_t *cart); // Read memory, can be from cart 
void bus_write(uint16_t addr, uint8_t data, cart_t *cart); // Write to memory, can be RAM from cart

uint16_t bus_read16(uint16_t addr, cart_t *cart);
void bus_write16(uint16_t addr, uint16_t data, cart_t *cart);