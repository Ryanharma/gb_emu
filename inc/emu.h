#pragma once

#include "common.h"
#include "cpu.h"
#include "cart.h"

// #define CLK_CYCLE 4.194304e6

typedef struct {
    bool paused;
    bool running;
    bool die;
    uint64_t ticks;
} emu_t;

void emu_cycles(int cpu_cycles);
int emu_run(int argc, char **argv, cart_t *cart, cpu_t *cpu);