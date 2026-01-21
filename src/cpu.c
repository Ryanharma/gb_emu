#include "cpu.h"

void fetch_data(cpu_t *cpu) {
    // Function that fetch data according to the addressing mode of the current instruction
    cpu->mem_dest    = 0;
    cpu->is_dest_mem = false;
    switch (cpu->cur_instruction.addr_mode) {
        case AM_NONE:
            return;
        case AM_R8_R8:
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
        case AM_R16_D16:
            uint8_t lsb = cpu->registers.PC;
            cpu->registers.PC++;
            uint8_t msb = cpu->registers.PC;
            cpu->registers.PC++;
            cpu->fetched_data = (msb << 8) | lsb;
        case AM_M16_R8:
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->mem_dest = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->is_dest_mem = true;
    }
}

void fetch_instruction(cpu_t *cpu, cart_t *cart) {
    // Function that fetch the next instruction given by the address of the pc
    cpu->cur_opcode = bus_read(cpu->registers.PC, cart);
    cpu->registers.PC++; // For 1 memory read
    cpu->cur_instruction = instruction_by_opcode(cpu->cur_opcode);
    if (&cpu->cur_instruction == NULL) {
        ERROR("The instruction couldn't be found in GB ISA !");
    }
}

void execute_instruction(cpu_t *cpu, cart_t *cart) {
    switch (cpu->cur_instruction.ins_type) {
        case INS_NOP:
            return;
        case INS_LD:
            if (cpu->is_dest_mem) {
                bus_write(cpu->registers.PC++, cpu->fetched_data, cart);
                cpu->registers.PC++;
                break;
            }
            else {
                break;
            }
        case INS_JP:
            // First let's implement it without any condition
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint8_t msb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint16_t addr = lsb | (msb << 8);
            cpu->registers.PC = addr;
            break;
        default:
            ERROR("INSTRUCTION TYPE UNDEFINED");
    }
    return;
}

void clock_cycle(cpu_t *cpu) {
    printf("NOT IMPLEMENTED YET\n");
}

void cpu_init(cpu_t *cpu) {
    cpu->registers.PC = 0x100;
    cpu->halted = false;
}

bool cpu_step(cpu_t *cpu, cart_t *cart) {
    if (!cpu->halted) {
        uint16_t pc = cpu->registers.PC;
        // printf("PC value 0x%2.2X\n", pc);
        fetch_instruction(cpu, cart);
        fetch_data(cpu);

        execute_instruction(cpu, cart);
        return true;
    }
    return false;
}

uint16_t cpu_read_reg(cpu_t *cpu, reg_t RT) {
    uint8_t msb;
    switch (RT) {
        // 8 bits registers
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
        
        // 16 bits registers 
        case RT_BC:
            msb = cpu->registers.B;
            cpu->registers.PC++;
            return ((msb << 8) | (cpu->registers.C));
        case RT_DE:
            msb = cpu->registers.D;
            cpu->registers.PC++;
            return ((msb << 8) | (cpu->registers.E));
        case RT_HL:
            msb = cpu->registers.H;
            cpu->registers.PC++;
            return ((msb << 8) | (cpu->registers.L));
        default:
            return 0xFF;
    }
}

void cpu_write_reg(cpu_t *cpu, reg_t RT, uint8_t data) {
    switch (RT) {
        // Only write 8 bits data (16 bits data would be written in 2 times)
        case RT_A:
            cpu->registers.A = data;
        case RT_B:
            cpu->registers.B = data;
        case RT_C:
            cpu->registers.C = data;
        case RT_D:
            cpu->registers.D = data;
        case RT_E:
            cpu->registers.E = data;
        case RT_H:
            cpu->registers.H = data;
        case RT_L:
            cpu->registers.L = data ;
        default:
            return;
    }
}