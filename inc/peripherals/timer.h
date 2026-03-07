#pragma once

#include "common.h"

#define CLK_FRQ (1 << 22)
#define M_FRQ CLK_FRQ/4

typedef struct {
    uint16_t sys_cnt; // System clk counter, the 8 MSBs of cnt are the bits of the div register 
    uint8_t tima;
    uint8_t tma;
    uint8_t tac;
} gb_timer_t;

extern gb_timer_t gb_timer;

void timer_init(gb_timer_t *timer);
void timer_step(gb_timer_t *timer);
void timer_write(gb_timer_t *timer, uint16_t addr, uint8_t value);
uint8_t timer_read(gb_timer_t *timer, uint16_t addr);