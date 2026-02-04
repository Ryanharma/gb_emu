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
    INS_NOT_IMPLEMENTED, // Needs to be first one to set by default
    INS_ADD,
    INS_ADC,
    INS_ADD16,
    INS_AND,
    INS_CALL,
    INS_CP,
    INS_CPL,
    INS_CCF,
    INS_DEC,
    INS_DEC16,
    INS_HALT,
    INS_INC,
    INS_INC16,
    INS_JP,
    INS_JR,
    INS_LD,
    INS_LD16,
    INS_NOP,
    INS_OR,
    INS_PUSH,
    INS_POP,
    INS_RET,
    INS_RETI,
    INS_RLC,
    INS_RRC,
    INS_RL,
    INS_RR,
    INS_RST,
    INS_SUB,
    INS_SBC,
    INS_STOP,
    INS_SCF,
    INS_XOR,
} asm_t;

typedef enum {
    AM_NONE,
    AM_R8_R8,
    AM_R8_D8,
    AM_R8_MR16,
    AM_MR16_R8,
    AM_MR16_D8,
    AM_R8_MD16,
    AM_MD16_R8,
    AM_MR16_D16,
    AM_R8_D16,
    AM_R8_MR8,
    AM_MR8_R8,
    AM_R8_MD8,
    AM_MD8_R8,
    AM_R8_HLM,
    AM_HLM_R8,
    AM_R8_HLP,
    AM_HLP_R8,
    AM_R16_D8,
    AM_R16_MD16,
    AM_MD16_R16,
    AM_R16_R16,
    AM_R16_SPP,
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

typedef enum {
    RST_00 = 0x00, 
    RST_08 = 0x08,
    RST_10 = 0x10,
    RST_18 = 0x18,
    RST_20 = 0x20,
    RST_28 = 0x28,
    RST_30 = 0x30,
    RST_38 = 0x38,
} rst_t;

typedef struct instruction {
    asm_t ins_type;
    addr_mode_t addr_mode;
    reg_t reg1;
    reg_t reg2;
    cond_t cond;
    rst_t rst;
} ins_t;

ins_t instruction_by_opcode(uint8_t opcode);
char *reg_by_instruction(reg_t reg);
// void ld_r8_r8(cpu_t cpu);
// void ld_r8_n(cpu_t cpu);
