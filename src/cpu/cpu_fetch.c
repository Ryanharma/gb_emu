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
        case AM_MR16_MR16: {
            uint16_t addr = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->fetched_data = bus_read(addr, cart);
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
            // Used also for jump instructions because of mem_dest being set correctly.
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
            cpu_write_reg16(cpu, cpu->cur_instruction.reg2, addr); // Write to register HL : HL--
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
            // printf("addr value = %d\n", addr);
            // printf("H = %2.2X / L = %2.2X\n", cpu->registers.H, cpu->registers.L);
            cpu_write_reg16(cpu, cpu->cur_instruction.reg2, addr); // Write to register HL : HL++
            // printf("H = %2.2X / L = %2.2X\n", cpu->registers.H, cpu->registers.L);
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
        case AM_R16_D8: {
            cpu->fetched_data = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            break;
        }
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
            break;
        }
        case AM_R16_R16: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            break;
        }
        case AM_R16_SPP: {
            int8_t e = (int8_t) bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint16_t SP = cpu_read_reg(cpu, cpu->cur_instruction.reg2);
            cpu->fetched_data = SP + e;
            uint16_t carry = get_carry_add(SP, e);
            // Set flags
            cpu->flags.h = (carry && (1 >> 3));
            cpu->flags.c = (carry && (1 >> 7));
            break;
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
    printf("Current PC/opcode: 0x%2.2X/0x%2.2X\n", cpu->registers.PC, cpu->cur_opcode);
    cpu->registers.PC++; // For 1 memory read
    cpu->cur_instruction = instruction_by_opcode(cpu->cur_opcode, &cb);
    if (&cpu->cur_instruction == NULL) {
        ERROR("The instruction couldn't be found in GB ISA !");
    }
    if (ime_reg)
        cpu->ime = 1; // Only if previous instruction was EI
}