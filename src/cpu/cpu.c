#include "cpu.h"
#include "interrupts.h"
#include "cpu_fetch.c"
#include "cpu_exec.c"

cpu_t gb_cpu = {0};

void cpu_init(cpu_t *cpu) {
    cpu->halted = false;
    // Set registers to default value for DMG
    cpu->registers.PC = 0x100;
    cpu->registers.SP = 0xFFFE;
    cpu->registers.A = 0x01;
    cpu->registers.C = 0x13;
    cpu->registers.E = 0xD8;
    cpu->registers.H = 0x01;
    cpu->registers.L = 0x4D;
    cpu->flags.z = 1;
    cpu->flags.h = 1;
    cpu->flags.c = 1;
}

// bool cpu_boot(cpu_t *cpu) {
//     while (!bus_read(0xFF50, cart), NULL) {
//         cpu_step(cpu, cart);
//     }
//     for (int addr = 0x02; addr <= 0xFF; addr++) {
//         uint8_t byte = bootrom_read(addr);
//         execute_instruction(cpu, NULL);
//         bus_write(0xFF50, 1, NULL);
//     }
//     return false;    
// }

bool cpu_step(cpu_t *cpu, cart_t *cart) {
    if (!cpu->halted) {
        if (cpu->ime && ((gb_interrupts.IE) & (gb_interrupts.IF))) {
            // Interrupt is handled only if ime flag is set and IE and IF registers have same bit set
            interrupt_handle(cpu, cart, &gb_interrupts);
        }
        else {
            fetch_instruction(cpu, cart);
            fetch_data(cpu, cart);
            execute_instruction(cpu, cart);
        }
        return true;
    }
    else {
        // CPU wakes up as soon as an interrupt is requested
        if (((gb_interrupts.IE) & (gb_interrupts.IF)) > 0) {
            cpu->halted = false;
            if (cpu->ime && ((gb_interrupts.IE) & (gb_interrupts.IF))) {
                // Interrupt is handled only if ime flag is set and IE and IF registers have same bit set
                interrupt_handle(cpu, cart, &gb_interrupts);
            }
        }
        return true;
    }
    return false;
}

uint16_t cpu_read_reg(cpu_t *cpu, reg_t RT) {
    switch (RT) {
        // 8 bit registers
        case RT_A:
            return cpu->registers.A;
        case RT_B:
            return cpu->registers.B;
        case RT_C:
            return cpu->registers.C;
        case RT_D:
            return cpu->registers.D;
        case RT_E:
            return cpu->registers.E;
        case RT_H:
            return cpu->registers.H;
        case RT_L:
            return cpu->registers.L;
        
        // 16 bit registers 
        case RT_AF: {
            uint8_t A = cpu->registers.A;
            uint8_t F = (cpu->flags.z << 7) | (cpu->flags.n << 6) | (cpu->flags.h << 5) | (cpu->flags.c << 4);
            return ((A << 8) | F);
        }
        case RT_BC: {
            uint8_t B = cpu->registers.B;
            uint8_t C = cpu->registers.C;
            return ((B << 8) | C);
        }
        case RT_DE: {
            uint8_t D = cpu->registers.D;
            uint8_t E = cpu->registers.E;
            return ((D << 8) | E);
        }
        case RT_HL: {
            uint8_t H = cpu->registers.H;
            uint8_t L = cpu->registers.L;
            return ((H << 8) | L);
        }
        default:
            return 0xFF;
    }
}

void cpu_write_reg(cpu_t *cpu, reg_t RT, uint8_t data) {
    switch (RT) {
        // 8 bit registers
        case RT_A: {
            cpu->registers.A = data;
            break;
        }
        case RT_B: {
            cpu->registers.B = data;
            break;
        }
        case RT_C: {
            cpu->registers.C = data;
            break;
        }
        case RT_D: {
            cpu->registers.D = data;
            break;
        }
        case RT_E: {
            cpu->registers.E = data;
            break;
        }
        case RT_H: {
            cpu->registers.H = data;
            break;
        }
        case RT_L: {
            cpu->registers.L = data;
            break;
        }
        default:
            break;
    }
    return;
}
void cpu_write_reg16(cpu_t *cpu, reg_t RT, uint16_t data) {
    uint8_t lsb = (data & 0xFF);
    uint8_t msb = (data >> 8);
    switch (RT) {
        // 16 bit registers
        case RT_AF: {
            // Set F flags
            cpu->flags.z = lsb && (1 << 7);
            cpu->flags.n = lsb && (1 << 6);
            cpu->flags.h = lsb && (1 << 5);
            cpu->flags.c = lsb && (1 << 4);
            cpu->registers.A = msb;
            break;
        }
        case RT_BC: {
            cpu->registers.C = lsb;
            cpu->registers.B = msb;
            break;
        }
        case RT_DE: {
            cpu->registers.E = lsb;
            cpu->registers.D = msb;
            break;
        }
        case RT_HL: {
            cpu->registers.L = lsb;
            cpu->registers.H = msb;
            break;
        }
    }
    return;
}

bool cpu_check_flag(cpu_t *cpu, cond_t CT) {
    switch (CT) {
        case CT_NONE:
            return true;
        case CT_Z: 
            return cpu->flags.z;
        case CT_NZ:
            return !(cpu->flags.z);
        case CT_C:
            return cpu->flags.c;
        case CT_NC:
            return !(cpu->flags.c);
        default:
            ERROR("Condition type for jump instruction not defined!");
    }
}

void print_cpu_state(cpu_t *cpu) {
    printf("GPRegs -> A = %x, B = %x, C = %x, D = %x, E = %x, H = %x, L = %x\n",
    cpu->registers.A, cpu->registers.B, cpu->registers.C, cpu->registers.D, cpu->registers.E, 
    cpu->registers.H, cpu->registers.L);
    printf("SP = %x\n", cpu->registers.SP);
    printf("PC = %x\n", cpu->registers.PC);
    printf("Opcode of instruction executed is: %x\n", cpu->cur_opcode);
}

uint16_t get_carry_add(uint16_t reg, int16_t e) {
    // The role of this function is to get the carry vector resulting from an addition.
    // This is important to set the flag register after an arithmetic operation was done.
    // It consist of the following operations (indexed from LSB to MSB): 
    // if i = 0: c(0) = reg(0) x e(0)
    // if i > 0: c(i) = reg(i) x e(i) + reg(i) x c(i-1) + e(i) x c(i-1)
    uint8_t c = 0; // Carry vector, constructed with or operations
    for (int i = 0; i < 2 * sizeof(int8_t) * 8; i++) {
        if (i == 0) {
            c |= (((reg & (1 << i)) && (e & (1 << i))) << i);
        }
        else {
            c |= ((((reg & (1 << i)) && (e & (1 << i))) << i) | (((reg & (1 << i)) && (c & (1 << (i-1)))) << i) | (((e & (1 << i)) && (c & (1 << (i-1)))) << i));
        }
    }
    return c;
}

int16_t CA2(uint16_t x) {
    // Return the CA2 (complement A2) of an unsigned integer for the substraction operation
    int16_t ca2_x;
    // 1 - Invert all the bits
    ca2_x = ~x;
    // 2 - Add 1 to get the CA2
    ca2_x += 1;
    
    return ca2_x;
}