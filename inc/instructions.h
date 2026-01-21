/* Code for instructions handled by GB CPU (ISA)
Instructions are: 
    - Load (8 or 16 bits data)
    - Arithmetic instructions
    - Rotate, shift and bit operation instructions
    - Jump instruction (control the flow of the GB program)
    - Others: NOP, HALT, STOP ...                                          
Some instructions may require multiple clock cycles so the cpu object 
is needed in those functions to emulate it.
*/

#pragma once

#include "common.h"

typedef enum {
    INS_NOT_IMPLEMENTED,
    INS_NOP,
    INS_STOP,
    INS_HALT,
    INS_LD,
    INS_INC,
    INS_DEC,
    INS_ADD,
    INS_JP,
} asm_t;

typedef enum {
    AM_NONE,
    AM_R8_R8,
    AM_R8_D8,
    AM_R8_M16,
    AM_M16_R8,
    AM_M16_D16,
    AM_R8_D16,
    AM_R8_M8,
    AM_M8_R8,
    AM_R16_D16,
} addr_mode_t;

typedef enum {
    RT_NONE,
    RT_A, RT_F, RT_AF,
    RT_B, RT_C, RT_BC,
    RT_D, RT_E, RT_DE,
    RT_H, RT_L, RT_HL,
    RT_SP,
    RT_PC,
} reg_t;

typedef enum {
    CT_NONE, CT_Z, CT_NZ, CT_C, CT_NC,
} cond_t;

typedef struct instruction {
    asm_t ins_type;
    addr_mode_t addr_mode;
    reg_t reg1;
    reg_t reg2;
    cond_t cond;
} ins_t;

ins_t instruction_by_opcode(uint8_t opcode);
// void ld_r8_r8(cpu_t cpu);
// void ld_r8_n(cpu_t cpu);
