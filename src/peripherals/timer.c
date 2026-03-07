#include "timer.h"
#include "interrupts.h"

static bool tima_overflow = false;
gb_timer_t gb_timer = {0};

void timer_init(gb_timer_t *timer) {
    timer->sys_cnt = 0xABCC;
}

void timer_step(gb_timer_t *timer) {
    uint16_t old_sys_cnt = timer->sys_cnt;
    timer->sys_cnt++; // Increment gb counter

    bool update_tima = false;

    // Handles multiplexing div register and falling edge detector
    switch (timer->tac & 0b11) {
        case 0b00: {
            update_tima = ((old_sys_cnt && (1 << 9)) && !(timer->sys_cnt && (1 << 9)));
            break;
        }
        case 0b01: {
            update_tima = ((old_sys_cnt && (1 << 3)) && !(timer->sys_cnt && (1 << 3)));
            break;
        }
        case 0b10: {
            update_tima = ((old_sys_cnt && (1 << 5)) && !(timer->sys_cnt && (1 << 5)));
            break;
        }
        case 0b11: {
            update_tima = ((old_sys_cnt && (1 << 7)) && !(timer->sys_cnt && (1 << 7)));
            break;
        }
        default: {
            ERROR("TAC register value undefined");
        }
    }

    // Handles tima register update + saturation
    if (update_tima && (timer->tac & 0b100)) {
        if (tima_overflow) {
            timer->tima = timer->tma;
            // IF interrupt signal set to 1 for timer (bit 3)
            gb_interrupt.IF |= 0b100;
        }
        else if (timer->tima + 1 > 0xFF) {
            tima_overflow = true;
        }
        timer->tima++;
    }
}

void timer_write(gb_timer_t *timer, uint16_t addr, uint8_t value) {
    switch (addr) {
        case (0xFF04): {
            // DIV register
            timer->sys_cnt &= ((value << 8) | 0xFF);
            break;
        }
        case (0xFF05): {
            // TIMA register
            timer->tima = value;
            break;
        }
        case (0xFF06): {
            // TMA register
            timer->tma = value << 8;
            break;
        }
        case (0xFF07): {
            // TAC register
            timer->tac = value;
            break;
        }
        default:
            ERROR("Undefined Address for GB timer subsystem") 
    }
}

uint8_t timer_read(gb_timer_t *timer, uint16_t addr) {
    switch (addr) {
        case (0xFF04): {
            // DIV register
            return (timer->sys_cnt >> 8);
        }
        case (0xFF05): {
            // TIMA register
            return timer->tima;
        }
        case (0xFF06): {
            // TMA register
            return timer->tma;
        }
        case (0xFF07): {
            // TAC register
            return timer->tac;
        }
        default:
            ERROR("Undefined Address for GB timer subsystem") 
    }
}
