#include "instructions.h"

ins_t instructions[0x100] = {
    
    // 0x0x FINISHED
    [0x00] = {INS_NOP},
    [0x01] = {INS_LD16, AM_R16_MD16, RT_BC},
    [0x02] = {INS_LD, AM_MR16_R8, RT_BC, RT_A},
    [0x03] = {INS_INC16, AM_NONE, RT_BC},
    [0x04] = {INS_INC, AM_R8_R8, RT_B},
    [0x05] = {INS_DEC, AM_R8_R8, RT_B},
    [0x06] = {INS_LD, AM_R8_D8, RT_B, RT_NONE},
    [0x07] = {INS_RLC, AM_R8_R8, RT_A},
    [0x08] = {INS_LD16, AM_MD16_R16, RT_NONE, RT_SP},
    [0x09] = {INS_ADD16, AM_R16_R16, RT_HL, RT_BC},
    [0x0A] = {INS_LD, AM_R8_MR16, RT_A, RT_BC},
    [0x0B] = {INS_DEC16, AM_NONE, RT_BC},
    [0x0C] = {INS_INC, AM_R8_R8, RT_C},
    [0x0D] = {INS_DEC, AM_R8_R8, RT_C},
    [0x0E] = {INS_LD, AM_R8_D8, RT_C, RT_NONE},
    [0x0F] = {INS_RRC, AM_R8_R8, RT_A},

    // 0x1x
    [0x11] = {INS_LD16, AM_R16_MD16, RT_DE, RT_NONE},
    [0x12] = {INS_LD, AM_MR16_R8, RT_DE, RT_A},
    [0x13] = {INS_INC16, AM_NONE, RT_DE},
    [0x14] = {INS_INC, AM_R8_R8, RT_D},
    [0x15] = {INS_DEC, AM_R8_R8, RT_D},
    [0x16] = {INS_LD, AM_R8_D8, RT_D, RT_NONE},
    [0x17] = {INS_RL, AM_R8_R8, RT_A},
    [0x18] = {INS_JR, AM_NONE, RT_NONE, RT_NONE, CT_NONE},
    [0x19] = {INS_ADD16, AM_R16_R16, RT_HL, RT_DE},
    [0x1A] = {INS_LD, AM_R8_MR16, RT_A, RT_DE},
    [0x1B] = {INS_DEC16, AM_NONE, RT_DE},
    [0x1C] = {INS_INC, AM_R8_R8, RT_E},
    [0x1D] = {INS_DEC, AM_R8_R8, RT_E},
    [0x1E] = {INS_LD, AM_R8_D8, RT_E, RT_NONE},
    [0x1F] = {INS_RR, AM_R8_R8, RT_A},

    // 0x2x
    [0x20] = {INS_JR, AM_NONE, RT_NONE, RT_NONE, CT_NZ},
    [0x21] = {INS_LD16, AM_R16_MD16, RT_HL, RT_NONE},
    [0x22] = {INS_LD, AM_HLP_R8, RT_HL, RT_A},
    [0x23] = {INS_INC16, AM_NONE, RT_HL},
    [0x24] = {INS_INC, AM_R8_R8, RT_H},
    [0x25] = {INS_DEC, AM_R8_R8, RT_H},
    [0x26] = {INS_LD, AM_R8_D8, RT_H, RT_NONE},
    [0x28] = {INS_JR, AM_NONE, RT_NONE, RT_NONE, CT_Z},
    [0x29] = {INS_ADD16, AM_R16_R16, RT_HL, RT_HL},
    [0x2A] = {INS_LD, AM_R8_HLP, RT_A, RT_HL},
    [0x2B] = {INS_DEC16, AM_NONE, RT_HL},
    [0x2C] = {INS_INC, AM_R8_R8, RT_L},
    [0x2D] = {INS_DEC, AM_R8_R8, RT_L},
    [0x2E] = {INS_LD, AM_R8_D8, RT_L, RT_NONE},
    [0x2F] = {INS_CPL},

    // 0x3x (FINISHED)
    [0x30] = {INS_JR, AM_NONE, RT_NONE, RT_NONE, CT_NC},
    [0x31] = {INS_LD16, AM_R16_MD16, RT_SP, RT_NONE},
    [0x32] = {INS_LD, AM_HLM_R8, RT_HL, RT_A},
    [0x33] = {INS_INC16, AM_NONE, RT_SP},
    [0x34] = {INS_INC, AM_MR16_R8, RT_HL},
    [0x35] = {INS_DEC, AM_MR16_R8, RT_HL},
    [0x36] = {INS_LD, AM_MR16_D8, RT_HL, RT_NONE},
    [0x37] = {INS_SCF},
    [0x38] = {INS_JR, AM_NONE, RT_NONE, RT_NONE, CT_C},
    [0x39] = {INS_ADD16, AM_R16_R16, RT_HL, RT_SP},
    [0x3A] = {INS_LD, AM_R8_HLM, RT_A, RT_HL},
    [0x3B] = {INS_DEC16, AM_NONE, RT_SP},
    [0x3C] = {INS_INC, AM_R8_R8, RT_A},
    [0x3D] = {INS_DEC, AM_R8_R8, RT_A},
    [0x3E] = {INS_LD, AM_R8_D8, RT_A, RT_NONE},
    [0x3F] = {INS_CCF},

    // 0x4x (FINISHED)
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

    // 0x5x (FINISHED)
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

    // 0x6x (FINISHED)
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
    // [0x76] = {INS_HALT},
    [0x77] = {INS_LD, AM_MR16_R8, RT_HL, RT_A},
    [0x78] = {INS_LD, AM_R8_R8, RT_A, RT_B},
    [0x79] = {INS_LD, AM_R8_R8, RT_A, RT_C},
    [0x7A] = {INS_LD, AM_R8_R8, RT_A, RT_D},
    [0x7B] = {INS_LD, AM_R8_R8, RT_A, RT_E},
    [0x7C] = {INS_LD, AM_R8_R8, RT_A, RT_H},
    [0x7D] = {INS_LD, AM_R8_R8, RT_A, RT_L},
    [0x7E] = {INS_LD, AM_R8_MR16, RT_A, RT_HL},
    [0x7F] = {INS_LD, AM_R8_R8, RT_A, RT_A},

    // 0x8x (FINISHED)
    [0x80] = {INS_ADD, AM_R8_R8, RT_NONE, RT_B}, // Adds to register A the second reg
    [0x81] = {INS_ADD, AM_R8_R8, RT_NONE, RT_C},
    [0x82] = {INS_ADD, AM_R8_R8, RT_NONE, RT_D},
    [0x83] = {INS_ADD, AM_R8_R8, RT_NONE, RT_E},
    [0x84] = {INS_ADD, AM_R8_R8, RT_NONE, RT_H},
    [0x85] = {INS_ADD, AM_R8_R8, RT_NONE, RT_L},
    [0x86] = {INS_ADD, AM_R8_MR16, RT_NONE, RT_HL},
    [0x87] = {INS_ADD, AM_R8_R8, RT_NONE, RT_A},
    [0x88] = {INS_ADC, AM_R8_R8, RT_NONE, RT_B},
    [0x89] = {INS_ADC, AM_R8_R8, RT_NONE, RT_C},
    [0x8A] = {INS_ADC, AM_R8_R8, RT_NONE, RT_D},
    [0x8B] = {INS_ADC, AM_R8_R8, RT_NONE, RT_E},
    [0x8C] = {INS_ADC, AM_R8_R8, RT_NONE, RT_H},
    [0x8D] = {INS_ADC, AM_R8_R8, RT_NONE, RT_L},
    [0x8E] = {INS_ADC, AM_R8_MR16, RT_NONE, RT_HL},
    [0x8F] = {INS_ADC, AM_R8_R8, RT_NONE, RT_A},

    // 0x9x (FINISHED)
    [0x90] = {INS_SUB, AM_R8_R8, RT_NONE, RT_B}, // Adds to register A the second reg
    [0x91] = {INS_SUB, AM_R8_R8, RT_NONE, RT_C},
    [0x92] = {INS_SUB, AM_R8_R8, RT_NONE, RT_D},
    [0x93] = {INS_SUB, AM_R8_R8, RT_NONE, RT_E},
    [0x94] = {INS_SUB, AM_R8_R8, RT_NONE, RT_H},
    [0x95] = {INS_SUB, AM_R8_R8, RT_NONE, RT_L},
    [0x96] = {INS_SUB, AM_R8_MR16, RT_NONE, RT_HL},
    [0x97] = {INS_SUB, AM_R8_R8, RT_NONE, RT_A},
    [0x98] = {INS_SBC, AM_R8_R8, RT_NONE, RT_B},
    [0x99] = {INS_SBC, AM_R8_R8, RT_NONE, RT_C},
    [0x9A] = {INS_SBC, AM_R8_R8, RT_NONE, RT_D},
    [0x9B] = {INS_SBC, AM_R8_R8, RT_NONE, RT_E},
    [0x9C] = {INS_SBC, AM_R8_R8, RT_NONE, RT_H},
    [0x9D] = {INS_SBC, AM_R8_R8, RT_NONE, RT_L},
    [0x9E] = {INS_SBC, AM_R8_MR16, RT_NONE, RT_HL},
    [0x9F] = {INS_SBC, AM_R8_R8, RT_NONE, RT_A},

    // 0xAx (FINISHED)
    [0xA0] = {INS_AND, AM_R8_R8, RT_NONE, RT_B}, // And to register A the second register
    [0xA1] = {INS_AND, AM_R8_R8, RT_NONE, RT_C},
    [0xA2] = {INS_AND, AM_R8_R8, RT_NONE, RT_D},
    [0xA3] = {INS_AND, AM_R8_R8, RT_NONE, RT_E},
    [0xA4] = {INS_AND, AM_R8_R8, RT_NONE, RT_H},
    [0xA5] = {INS_AND, AM_R8_R8, RT_NONE, RT_L},
    [0xA6] = {INS_AND, AM_R8_MR16, RT_NONE, RT_HL},
    [0xA7] = {INS_AND, AM_R8_R8, RT_NONE, RT_A},
    [0xA8] = {INS_XOR, AM_R8_R8, RT_NONE, RT_B}, // Xor to register A the second register
    [0xA9] = {INS_XOR, AM_R8_R8, RT_NONE, RT_C},
    [0xAA] = {INS_XOR, AM_R8_R8, RT_NONE, RT_D},
    [0xAB] = {INS_XOR, AM_R8_R8, RT_NONE, RT_E},
    [0xAC] = {INS_XOR, AM_R8_R8, RT_NONE, RT_H},
    [0xAD] = {INS_XOR, AM_R8_R8, RT_NONE, RT_L},
    [0xAE] = {INS_XOR, AM_R8_MR16, RT_NONE, RT_HL},
    [0xAF] = {INS_XOR, AM_R8_R8, RT_NONE, RT_A},

    // 0xBx (FINISHED)
    [0xB0] = {INS_OR, AM_R8_R8, RT_NONE, RT_B}, // OR to register A the second register
    [0xB1] = {INS_OR, AM_R8_R8, RT_NONE, RT_C},
    [0xB2] = {INS_OR, AM_R8_R8, RT_NONE, RT_D},
    [0xB3] = {INS_OR, AM_R8_R8, RT_NONE, RT_E},
    [0xB4] = {INS_OR, AM_R8_R8, RT_NONE, RT_H},
    [0xB5] = {INS_OR, AM_R8_R8, RT_NONE, RT_L},
    [0xB6] = {INS_OR, AM_R8_MR16, RT_NONE, RT_HL},
    [0xB7] = {INS_OR, AM_R8_R8, RT_NONE, RT_A},
    [0xB8] = {INS_CP, AM_R8_R8, RT_NONE, RT_B}, // Substract A to 2nd register but doesn't store result
    [0xB9] = {INS_CP, AM_R8_R8, RT_NONE, RT_C},
    [0xBA] = {INS_CP, AM_R8_R8, RT_NONE, RT_D},
    [0xBB] = {INS_CP, AM_R8_R8, RT_NONE, RT_E},
    [0xBC] = {INS_CP, AM_R8_R8, RT_NONE, RT_H},
    [0xBD] = {INS_CP, AM_R8_R8, RT_NONE, RT_L},
    [0xBE] = {INS_CP, AM_R8_MR16, RT_NONE, RT_HL},
    [0xBF] = {INS_CP, AM_R8_R8, RT_NONE, RT_A},

    // 0xCx MISSES PREFIX CB
    [0xC0] = {INS_RET, AM_NONE, RT_NONE, RT_NONE, CT_NZ},
    [0xC1] = {INS_POP, AM_NONE, RT_BC},
    [0xC2] = {INS_JP, AM_MD16_R8, RT_NONE, RT_NONE, CT_NZ},
    [0xC3] = {INS_JP, AM_MD16_R8, RT_NONE, RT_NONE, CT_NONE},
    [0xC4] = {INS_CALL, AM_NONE, RT_NONE, RT_NONE, CT_NZ},
    [0xC5] = {INS_PUSH, AM_NONE, RT_BC},
    [0xC6] = {INS_ADD, AM_R8_D8, RT_NONE, RT_NONE},
    [0xC7] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_00},
    [0xC8] = {INS_RET, AM_NONE, RT_NONE, RT_NONE, CT_Z},
    [0xC9] = {INS_RET, AM_NONE, RT_NONE, RT_NONE, CT_NONE},
    [0xCA] = {INS_JP, AM_MD16_R8, RT_NONE, RT_NONE, CT_Z},
    [0xCC] = {INS_CALL, AM_NONE, RT_NONE, RT_NONE, CT_Z},
    [0xCD] = {INS_RET, AM_NONE, RT_NONE, RT_NONE, CT_NONE},
    [0xCE] = {INS_ADC, AM_R8_D8, RT_NONE, RT_NONE},
    [0xCF] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_08},

    // 0xDx FINISHED
    [0xD0] = {INS_RET, AM_NONE, RT_NONE, RT_NONE, CT_NC},
    [0xD1] = {INS_POP, AM_NONE, RT_DE},
    [0xD2] = {INS_JP, AM_MD16_R8, RT_NONE, RT_NONE, CT_NC},
    [0xD4] = {INS_CALL, AM_NONE, RT_NONE, RT_NONE, CT_NC},
    [0xD5] = {INS_PUSH, AM_NONE, RT_DE},
    [0xD6] = {INS_SUB, AM_R8_D8, RT_NONE, RT_NONE},
    [0xD7] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_10},
    [0xD8] = {INS_RET, AM_NONE, RT_NONE, RT_NONE, CT_C},
    [0xD9] = {INS_RETI},
    [0xDA] = {INS_JP, AM_MD16_R8, RT_NONE, RT_NONE, CT_C},
    [0xDC] = {INS_CALL, AM_NONE, RT_NONE, RT_NONE, CT_C},
    [0xDE] = {INS_SBC, AM_R8_D8, RT_NONE, RT_NONE},
    [0xDF] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_18},

    // 0xEx FINISHED
    [0xE0] = {INS_LD, AM_MD8_R8, RT_NONE, RT_A},
    [0xE1] = {INS_POP, AM_NONE, RT_HL},
    [0xE2] = {INS_LD, AM_MR8_R8, RT_C, RT_A},
    [0xE5] = {INS_PUSH, AM_NONE, RT_HL},
    [0xE6] = {INS_AND, AM_R8_D8, RT_NONE, RT_NONE},
    [0xE7] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_20},
    [0xE8] = {INS_ADD16, AM_R16_D8, RT_SP},
    [0xE9] = {INS_JP, AM_MR16_R8, RT_HL, RT_NONE, CT_NONE}, // Jump address specified by reg1
    [0xEA] = {INS_LD, AM_MD16_R8, RT_NONE, RT_A},
    [0xEE] = {INS_XOR, AM_R8_D8, RT_NONE, RT_NONE},
    [0xEF] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_28},

    // 0xFx
    [0xF0] = {INS_LD, AM_R8_MD8, RT_A, RT_NONE},
    [0xF1] = {INS_POP, AM_NONE, RT_AF},
    [0xF2] = {INS_LD, AM_R8_MR8, RT_A, RT_C},
    [0xF5] = {INS_PUSH, AM_NONE, RT_AF},
    [0xF6] = {INS_OR, AM_R8_D8, RT_NONE, RT_NONE},
    [0xF7] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_30},
    [0xF8] = {INS_LD16, AM_R16_SPP, RT_HL, RT_SP},
    [0xF9] = {INS_LD, AM_R16_R16, RT_SP, RT_HL},
    [0xFA] = {INS_LD, AM_R8_MD16, RT_A, RT_NONE},
    [0xFE] = {INS_CP, AM_R8_D8, RT_NONE, RT_NONE},
    [0xFF] = {INS_RST, AM_NONE, RT_NONE, RT_NONE, CT_NONE, RST_38},
};

ins_t instruction_by_opcode(uint8_t opcode) {
    if (opcode < 0x100) {
        return instructions[opcode];
    }
}

char *reg_by_instruction(reg_t reg) {
    switch (reg) {
        case RT_A:
            return "A";
        case RT_F:
            return "F";
        case RT_AF:
            return "AF";
        case RT_B:
            return "B";
        case RT_C:
            return "C";
        case RT_BC:
            return "BC";
        case RT_D:
            return "D";
        case RT_E:
            return "E";
        case RT_DE:
            return "DE";
        case RT_H:
            return "H";
        case RT_L:
            return "L";
        case RT_HL:
            return "HL"; 
        case RT_SP:
            return "SP";
        case RT_PC:
            return "PC";
        default:
            ERROR("UNKNOWN REG");
    }
}