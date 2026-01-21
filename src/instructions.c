#include "instructions.h"

ins_t instructions[0x100] = {
    [0x00] = {INS_NOP},
    [0x01] = {INS_LD, AM_R16_D16, RT_BC},
    [0x02] = {INS_LD, AM_M16_R8, RT_BC, RT_A},

    [0xC2] = {INS_JP, RT_NONE, RT_NONE, CT_NZ},
    [0xC3] = {INS_JP, RT_NONE, RT_NONE, CT_NONE},
};

ins_t instruction_by_opcode(uint8_t opcode) {
    if (opcode < 0x100) {
        return instructions[opcode];
    }
}