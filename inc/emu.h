#pragma once

#include "common.h"
#include "cpu.h"
#include "bus.h"
#include "cart.h"
#include "time.h"

typedef struct {
    bool paused;
    bool running;
    bool die;
    uint64_t ticks;
} emu_t;

void emu_cycles(int cpu_cycles);
int emu_run(int argc, char **argv, cart_t *cart, cpu_t *cpu);