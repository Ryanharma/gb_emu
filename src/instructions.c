#include "instructions.h"

ins_t instructions[0x100] = {
    // 0x0x
    [0x00] = {INS_NOP},
    [0x01] = {INS_LD16, AM_R16_MD16, RT_BC},
    [0x02] = {INS_LD, AM_MR16_R8, RT_BC, RT_A},
    [0x06] = {INS_LD, AM_R8_D8, RT_B, RT_NONE},
    [0x08] = {INS_LD16, AM_MD16_R16, RT_NONE, RT_SP},
    [0x0A] = {INS_LD, AM_R8_MR16, RT_A, RT_BC},
    [0x0E] = {INS_LD, AM_R8_D8, RT_C, RT_NONE},

    // 0x1x
    [0x11] = {INS_LD16, AM_R16_MD16, RT_DE, RT_NONE},
    [0x12] = {INS_LD, AM_MR16_R8, RT_DE, RT_A},
    [0x16] = {INS_LD, AM_R8_D8, RT_D, RT_NONE},
    [0x1A] = {INS_LD, AM_R8_MR16, RT_A, RT_DE},
    [0x1E] = {INS_LD, AM_R8_D8, RT_E, RT_NONE},

    // 0x2x
    [0x21] = {INS_LD16, AM_R16_MD16, RT_HL, RT_NONE},
    [0x22] = {INS_LD, AM_HLP_R8, RT_HL, RT_A},
    [0x26] = {INS_LD, AM_R8_D8, RT_H, RT_NONE},
    [0x2A] = {INS_LD, AM_R8_HLP, RT_A, RT_HL},
    [0x2E] = {INS_LD, AM_R8_D8, RT_L, RT_NONE},

    // 0x3x
    [0x31] = {INS_LD16, AM_R16_MD16, RT_SP, RT_NONE},
    [0x32] = {INS_LD, AM_HLM_R8, RT_HL, RT_A},
    [0x36] = {INS_LD, AM_MR16_D8, RT_HL, RT_NONE},
    [0x3A] = {INS_LD, AM_R8_HLM, RT_A, RT_HL},
    [0x3E] = {INS_LD, AM_R8_D8, RT_A, RT_NONE},

    // 0x4x
    [0x40] = {INS_LD, AM_R8_R8, RT_B, RT_B}, 
    [0x41] = {INS_LD, AM_R8_R8, RT_B, RT_C},
    [0x42] = {INS_LD, AM_R8_R8, RT_B, RT_D},
    [0x43] = {INS_LD, AM_R8_R8, RT_B, RT_E},
    [0x44] = {INS_LD, AM_R8_R8, RT_B, RT_H},
    [0x45] = {INS_LD, AM_R8_R8, RT_B, RT_L},
    [0x46] = {INS_LD, AM_R8_MR16, RT_B, RT_HL},
    [0x47] = {INS_LD, AM_R8_R8, RT_B, RT_A},
    [0x48] = {INS_LD, AM_R8_R8, RT_C, RT_B},
    [0x49] = {INS_LD, AM_R8_R8, RT_C, RT_C},
    [0x4A] = {INS_LD, AM_R8_R8, RT_C, RT_D},
    [0x4B] = {INS_LD, AM_R8_R8, RT_C, RT_E},
    [0x4C] = {INS_LD, AM_R8_R8, RT_C, RT_H},
    [0x4D] = {INS_LD, AM_R8_R8, RT_C, RT_L},
    [0x4E] = {INS_LD, AM_R8_MR16, RT_C, RT_HL},
    [0x4F] = {INS_LD, AM_R8_R8, RT_C, RT_A},

    // 0x5x
    [0x50] = {INS_LD, AM_R8_R8, RT_D, RT_B}, 
    [0x51] = {INS_LD, AM_R8_R8, RT_D, RT_C},
    [0x52] = {INS_LD, AM_R8_R8, RT_D, RT_D},
    [0x53] = {INS_LD, AM_R8_R8, RT_D, RT_E},
    [0x54] = {INS_LD, AM_R8_R8, RT_D, RT_H},
    [0x55] = {INS_LD, AM_R8_R8, RT_D, RT_L},
    [0x56] = {INS_LD, AM_R8_MR16, RT_D, RT_HL},
    [0x57] = {INS_LD, AM_R8_R8, RT_D, RT_A},
    [0x58] = {INS_LD, AM_R8_R8, RT_E, RT_B},
    [0x59] = {INS_LD, AM_R8_R8, RT_E, RT_C},
    [0x5A] = {INS_LD, AM_R8_R8, RT_E, RT_D},
    [0x5B] = {INS_LD, AM_R8_R8, RT_E, RT_E},
    [0x5C] = {INS_LD, AM_R8_R8, RT_E, RT_H},
    [0x5D] = {INS_LD, AM_R8_R8, RT_E, RT_L},
    [0x5E] = {INS_LD, AM_R8_MR16, RT_E, RT_HL},
    [0x5F] = {INS_LD, AM_R8_R8, RT_E, RT_A},

    // 0x6x
    [0x60] = {INS_LD, AM_R8_R8, RT_H, RT_B}, 
    [0x61] = {INS_LD, AM_R8_R8, RT_H, RT_C},
    [0x62] = {INS_LD, AM_R8_R8, RT_H, RT_D},
    [0x63] = {INS_LD, AM_R8_R8, RT_H, RT_E},
    [0x64] = {INS_LD, AM_R8_R8, RT_H, RT_H},
    [0x65] = {INS_LD, AM_R8_R8, RT_H, RT_L},
    [0x66] = {INS_LD, AM_R8_MR16, RT_H, RT_HL},
    [0x67] = {INS_LD, AM_R8_R8, RT_H, RT_A},
    [0x68] = {INS_LD, AM_R8_R8, RT_L, RT_B},
    [0x69] = {INS_LD, AM_R8_R8, RT_L, RT_C},
    [0x6A] = {INS_LD, AM_R8_R8, RT_L, RT_D},
    [0x6B] = {INS_LD, AM_R8_R8, RT_L, RT_E},
    [0x6C] = {INS_LD, AM_R8_R8, RT_L, RT_H},
    [0x6D] = {INS_LD, AM_R8_R8, RT_L, RT_L},
    [0x6E] = {INS_LD, AM_R8_MR16, RT_L, RT_HL},
    [0x6F] = {INS_LD, AM_R8_R8, RT_L, RT_A},

    // 0x7x
    [0x70] = {INS_LD, AM_MR16_R8, RT_HL, RT_B}, 
    [0x71] = {INS_LD, AM_MR16_R8, RT_HL, RT_C},
    [0x72] = {INS_LD, AM_MR16_R8, RT_HL, RT_D},
    [0x73] = {INS_LD, AM_MR16_R8, RT_HL, RT_E},
    [0x74] = {INS_LD, AM_MR16_R8, RT_HL, RT_H},
    [0x75] = {INS_LD, AM_MR16_R8, RT_HL, RT_L},
    [0x76] = {INS_HALT},
    [0x77] = {INS_LD, AM_MR16_R8, RT_HL, RT_A},
    [0x78] = {INS_LD, AM_R8_R8, RT_A, RT_B},
    [0x79] = {INS_LD, AM_R8_R8, RT_A, RT_C},
    [0x7A] = {INS_LD, AM_R8_R8, RT_A, RT_D},
    [0x7B] = {INS_LD, AM_R8_R8, RT_A, RT_E},
    [0x7C] = {INS_LD, AM_R8_R8, RT_A, RT_H},
    [0x7D] = {INS_LD, AM_R8_R8, RT_A, RT_L},
    [0x7E] = {INS_LD, AM_R8_MR16, RT_A, RT_HL},
    [0x7F] = {INS_LD, AM_R8_R8, RT_A, RT_A},

    // 0xCx
    [0xC2] = {INS_JP, RT_NONE, RT_NONE, CT_NZ},
    [0xC3] = {INS_JP, RT_NONE, RT_NONE, CT_NONE},

    // 0xEx
    [0xE0] = {INS_LD, AM_MD8_R8, RT_NONE, RT_A},
    [0xE2] = {INS_LD, AM_MR8_R8, RT_C, RT_A},
    [0xEA] = {INS_LD, AM_MD16_R8, RT_NONE, RT_A},

    // 0xFx
    [0xF0] = {INS_LD, AM_R8_MD8, RT_A, RT_NONE},
    [0xF2] = {INS_LD, AM_R8_MR8, RT_A, RT_C},
    [0xF9] = {INS_LD, AM_R16_R16, RT_SP, RT_HL},
    [0xFA] = {INS_LD, AM_R8_MD16, RT_A, RT_NONE},
};

ins_t instruction_by_opcode(uint8_t opcode) {
    if (opcode < 0x100) {
        return instructions[opcode];
    }
}