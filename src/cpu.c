#include "cpu.h"

void fetch_data(cpu_t *cpu, cart_t *cart) {
    // Function that fetch data according to the addressing mode of the current instruction
    cpu->mem_dest    = 0;
    cpu->is_dest_mem = false;
    switch (cpu->cur_instruction.addr_mode) {
        case AM_NONE:
            break;
        // 8 bit Load Instructions
        case AM_R8_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            break;
        }
        case AM_R8_D8: {
            cpu->fetched_data = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            break;
        }
        case AM_R8_MR16: {
            uint16_t addr = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->fetched_data = bus_read(addr, cart);
            break;
        }
        case AM_MR16_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->mem_dest = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->is_dest_mem = true;
            break;
        }
        case AM_MR16_D8: {
            cpu->fetched_data = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            cpu->mem_dest = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->is_dest_mem = true;
            break;
        }
        case AM_R8_MD16: {
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint8_t msb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint16_t addr = lsb | (msb << 8);
            cpu->fetched_data = bus_read(addr, cart);
            break;
        }
        case AM_MD16_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint8_t msb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            cpu->mem_dest = lsb | (msb << 8);
            cpu->is_dest_mem = true;
            break;
        }
        case AM_R8_MR8: {
            uint8_t lsb = cpu_read_reg(cpu, cpu->cur_instruction.reg2); 
            uint16_t addr = lsb | (0xFF << 8);
            cpu->fetched_data = bus_read(addr, cart); // No PC++ because of the fetch/execute overlap
            break;
        }
        case AM_MR8_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            uint8_t lsb = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->mem_dest = lsb | (0xFF << 8);
            cpu->is_dest_mem = true;
            break;
        }
        case AM_R8_MD8: {
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint16_t addr = lsb | (0xFF << 8);
            cpu->fetched_data = bus_read(addr, cart);
            break;
        }
        case AM_MD8_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            cpu->mem_dest = lsb | (0xFF << 8);
            cpu->is_dest_mem = true;
            break;
        }
        case AM_R8_HLM: {
            uint16_t addr = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->fetched_data = bus_read(addr, cart);
            addr--;
            cpu_write_reg(cpu, cpu->cur_instruction.reg2, addr); // Write to register HL : HL--
            break;
        }
        case AM_HLM_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->mem_dest = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->is_dest_mem = true;
            // Decrement HL after reading the data pointed by it's address
            uint16_t data = cpu->mem_dest--;
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, data);
            break;
        }
        case AM_R8_HLP: {
            uint16_t addr = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->fetched_data = bus_read(addr, cart);
            addr++;
            cpu_write_reg(cpu, cpu->cur_instruction.reg2, addr); // Write to register HL : HL--
            break;       
        }
        case AM_HLP_R8: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->mem_dest = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->is_dest_mem = true;
            // Decrement HL after reading the data pointed by it's address
            uint16_t data = cpu->mem_dest++;
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, data);
            break;
        }
        // 16-bit Load Instructions
        case AM_R16_MD16: {
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint8_t msb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            cpu->fetched_data = (msb << 8) | lsb;
            break;
        }
        case AM_MD16_R16: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint8_t msb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            cpu->mem_dest = (msb << 8) | lsb;
            cpu->is_dest_mem;
        }
        case AM_R16_R16: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
        }
        default: {
            ERROR("INVALID ADDRESSING MODE");
        }
    }
    return;
}

void fetch_instruction(cpu_t *cpu, cart_t *cart) {
    // Function that fetch the next instruction given by the address of the pc
    cpu->cur_opcode = bus_read(cpu->registers.PC, cart);
    printf("Current instruction opcode: 0x%2.2X\n", cpu->cur_opcode);
    cpu->registers.PC++; // For 1 memory read
    cpu->cur_instruction = instruction_by_opcode(cpu->cur_opcode);
    if (&cpu->cur_instruction == NULL) {
        ERROR("The instruction couldn't be found in GB ISA !");
    }
}

void execute_instruction(cpu_t *cpu, cart_t *cart) {
    switch (cpu->cur_instruction.ins_type) {
        case INS_NOP:
            printf("NOP\n");
            break;
        case INS_LD:
            if (cpu->is_dest_mem) {
                printf("M[0x%2.2X] = %2.2X\n", cpu->mem_dest, cpu->fetched_data);
                bus_write(cpu->mem_dest, cpu->fetched_data, cart);
                // cpu->registers.PC++; // No PC++ for fetch/execute overlap technique
                break;
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, cpu->fetched_data);
                printf("LD %d to register %s\n", cpu->fetched_data, reg_by_instruction(cpu->cur_instruction.reg1));
                break;
            }
        case INS_LD16:
            // Fetched data is actually 16 bits in this case
            if (cpu->is_dest_mem) {
                uint8_t lsb = cpu->fetched_data && 0xFF;
                uint8_t msb = cpu->fetched_data >> 8;
                bus_write(cpu->mem_dest, lsb, cart);
                printf("M[%X] = %X\n", cpu->mem_dest, lsb);
                cpu->mem_dest++;
                bus_write(cpu->mem_dest, msb, cart);
                printf("M[%X] = %X\n", cpu->mem_dest, msb);
                break;
            }
            else {
                cpu_write_reg16(cpu, cpu->cur_instruction.reg1, cpu->fetched_data);
                printf("LD %d to register %s\n", cpu->fetched_data, reg_by_instruction(cpu->cur_instruction.reg1));
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
            printf("JP 0x%2.2x\n", addr);
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
        // uint16_t pc = cpu->registers.PC;
        // printf("PC value 0x%2.2X\n", pc);
        fetch_instruction(cpu, cart);
        fetch_data(cpu, cart);
        execute_instruction(cpu, cart);
        return true;
    }
    return false;
}

uint16_t cpu_read_reg(cpu_t *cpu, reg_t RT) {
    uint8_t msb;
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
        case RT_BC: {
            msb = cpu->registers.B;
            // cpu->registers.PC++;
            return ((msb << 8) | (cpu->registers.C));
        }
        case RT_DE: {
            msb = cpu->registers.D;
            // cpu->registers.PC++;
            return ((msb << 8) | (cpu->registers.E));
        }
        case RT_HL: {
            msb = cpu->registers.H;
            // cpu->registers.PC++;
            return ((msb << 8) | (cpu->registers.L));
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
            // cpu->registers.F = lsb; // No load operation with AF
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