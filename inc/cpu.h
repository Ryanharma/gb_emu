// Code for internal cpu functionality so mainly it's registers' state + clk

#pragma once

#include "common.h"
#include "instructions.h"
#include "cart.h"
#include "bus.h"

typedef struct cpu_reg {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;
    uint16_t SP;
    uint16_t PC;
} cpu_reg_t;

typedef struct reg_flag {
    bool z; // Zero flag
    bool n; // Add-sub flag for negative (BCD)
    bool h; // half carry flag (BCD)
    bool c; // Carry flag
    // Remaining bits of this 8 bits register are not used ... 
} flag_t;

typedef struct cpu {
    cpu_reg_t registers;
    flag_t flags;
    ins_t cur_instruction;
    uint16_t fetched_data;
    uint16_t mem_dest;
    uint8_t cur_opcode;
    bool is_dest_mem;
    bool halted;
} cpu_t;

void clock_cycle(cpu_t *cpu);
void cpu_init(cpu_t *cpu);
bool cpu_step(cpu_t *cpu, cart_t *cart);
uint16_t cpu_read_reg(cpu_t *cpu, reg_t RT);
void cpu_write_reg(cpu_t *cpu, reg_t RT, uint8_t data);
void cpu_write_reg16(cpu_t *cpu, reg_t RT, uint16_t data);
void fetch_instruction(cpu_t *cpu, cart_t *cart);
void fetch_data(cpu_t *cpu, cart_t *cart);
void execute_instruction(cpu_t *cpu, cart_t *cart);
uint8_t get_carry_add(uint16_t reg, int8_t e);
int16_t CA2(uint16_t x);