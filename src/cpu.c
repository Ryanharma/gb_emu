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
    cpu->cur_instruction = instruction_by_opcode(cpu->cur_opcode, &cpu->cb_mode);
    if (&cpu->cur_instruction == NULL) {
        ERROR("The instruction couldn't be found in GB ISA !");
    }
}

void execute_instruction(cpu_t *cpu, cart_t *cart) {
    switch (cpu->cur_instruction.ins_type) {
        case INS_NOP: {
            printf("NOP\n");
            break;
        }
        case INS_LD: {
            if (cpu->is_dest_mem) {
                printf("M[0x%2.2X] = %2.2X\n", cpu->mem_dest, cpu->fetched_data);
                bus_write(cpu->mem_dest, cpu->fetched_data, cart);
                break;
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, cpu->fetched_data);
                printf("LD 0x%x to register %s\n", cpu->fetched_data, reg_by_instruction(cpu->cur_instruction.reg1));
                break;
            }
        }
        case INS_LD16: {
            // Fetched data is actually 16 bits in this case
            if (cpu->is_dest_mem) {
                uint8_t lsb = cpu->fetched_data && 0xFF;
                uint8_t msb = cpu->fetched_data >> 8;
                bus_write(cpu->mem_dest, lsb, cart);
                printf("M[%X] = %X\n", cpu->mem_dest, lsb);
                cpu->mem_dest++;
                bus_write(cpu->mem_dest, msb, cart);
                printf("M[%X] = %X\n", cpu->mem_dest, msb);
            }
            else {
                cpu_write_reg16(cpu, cpu->cur_instruction.reg1, cpu->fetched_data);
                printf("LD 0x%x to register %s\n", cpu->fetched_data, reg_by_instruction(cpu->cur_instruction.reg1));
            }
            break;
        }
        case INS_PUSH: {
            cpu->fetched_data = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu->registers.SP--;
            bus_write(cpu->registers.SP, (cpu->fetched_data) >> 8, cart); // Write MSB of fetched data
            cpu->registers.SP--;
            bus_write(cpu->registers.SP, (cpu->fetched_data) & 0xFF, cart); // Write LSB of fetched data
            printf("PUSH from %s to memory %x / SP = %x\n", reg_by_instruction(cpu->cur_instruction.reg1), cpu->fetched_data, cpu->registers.SP);
            break;
        }
        case INS_POP: {
            uint8_t lsb = bus_read(cpu->registers.SP, cart);
            cpu->registers.SP++;
            uint8_t msb = bus_read(cpu->registers.SP, cart);
            cpu->registers.SP++;
            uint16_t data = lsb | (msb << 8);
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, data);
            printf("POP to %s = %x / SP = %x\n", reg_by_instruction(cpu->cur_instruction.reg1), data, cpu->registers.SP);
        }
        case INS_JP: {
            if (cpu_check_flag(cpu, cpu->cur_instruction.cond))
                cpu->registers.PC = cpu->mem_dest;
            printf("JP 0x%2.2x\n", cpu->mem_dest);
            break;
        }

        case INS_JR: {
            int8_t e = bus_read(cpu->registers.PC, cart); // Signed operand
            cpu->registers.PC++;
            if (cpu_check_flag(cpu, cpu->cur_instruction.cond))
                cpu->registers.PC += e;
            printf("JR 0x%2.2x\n", cpu->registers.PC);
            break;
        }

        case INS_CALL: {
            uint8_t lsb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint8_t msb = bus_read(cpu->registers.PC, cart);
            cpu->registers.PC++;
            uint16_t mem_dest = msb << 8 | lsb;
            if (cpu_check_flag(cpu, cpu->cur_instruction.cond)) {
                cpu->registers.SP--; // Push to stack return address of the function
                bus_write(cpu->registers.SP, cpu->registers.PC >> 8, cart); // Write MSB of current PC
                cpu->registers.SP--;
                bus_write(cpu->registers.SP, cpu->registers.PC & 0xFF, cart);
                cpu->registers.PC = mem_dest;
                printf("CALL 0x%2.2X\n", mem_dest);
            }
            break;
        }

        case INS_RET: {
            if (cpu_check_flag(cpu, cpu->cur_instruction.cond)) {
                uint8_t lsb = bus_read(cpu->registers.SP, cart);
                cpu->registers.SP++;
                uint8_t msb = bus_read(cpu->registers.SP, cart);
                cpu->registers.SP++;
                uint16_t ret_addr = msb << 8 | lsb;
                cpu->registers.PC = ret_addr;
                printf("RET 0x%2.2X\n", ret_addr);
            }
            break;
        }

        case INS_RETI: {
            uint8_t lsb = bus_read(cpu->registers.SP, cart);
            cpu->registers.SP++;
            uint8_t msb = bus_read(cpu->registers.SP, cart);
            cpu->registers.SP++;
            uint16_t ret_addr = msb << 8 | lsb;
            cpu->registers.PC = ret_addr;
            cpu->ime = true;
            printf("RETI 0x%2.2X\n", ret_addr);
            break;
        }

        case INS_RST: {
            // Call to function with HC jump address
            cpu->registers.SP--;
            bus_write(cpu->registers.SP, cpu->registers.PC >> 8, cart);
            cpu->registers.SP--;
            bus_write(cpu->registers.SP, cpu->registers.PC & 0xFF, cart);
            cpu->registers.PC = cpu->cur_instruction.rst;
            printf("RST 0x%2.2X\n", cpu->registers.PC);
            break;
        }

        // Arithmetical instructions
        case INS_INC: {
            uint8_t res;
            uint16_t carry;
            if (cpu->is_dest_mem) {
                uint16_t data = bus_read(cpu->mem_dest, cart);
                carry = get_carry_add(data, 1);
                res = data + 1;
                bus_write(cpu->mem_dest, res, cart);
                printf("Memory at address %x incremented to value %x\n", cpu->mem_dest, res);
            }
            else {
                // Destination is a register
                uint16_t reg = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
                carry = get_carry_add(reg, 1);
                res = reg + 1;
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
                printf("Register %s incremented to value %d\n", reg_by_instruction(cpu->cur_instruction.reg1), res);
            }
            cpu->flags.z = (res == 0);
            cpu->flags.n = 0;
            cpu->flags.h = carry && (1 >> 3);
            break;
        }
        case INS_INC16: {
            uint16_t reg = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, reg + 1);
            break;
        }
        case INS_DEC: {
            uint8_t res;
            uint16_t carry;
            if (cpu->is_dest_mem) {
                uint16_t data = bus_read(cpu->mem_dest, cart);
                carry = get_carry_add(data, 0xFF);
                res = data - 1;
                bus_write(cpu->mem_dest, res, cart);
                printf("Memory at address %x decremented to value %x\n", cpu->mem_dest, res);
            }
            else {
                // Destination is a register
                uint16_t reg = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
                carry = get_carry_add(reg, 0xFF);
                res = reg - 1;
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
                printf("Register %s decremented to value %x\n", reg_by_instruction(cpu->cur_instruction.reg1), res);
                // Set flags
            }
            break;
        }
        case INS_DEC16: {
            uint16_t reg = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, reg - 1);
            break;
        }
        case INS_ADD: {
            uint16_t carry = get_carry_add(cpu->registers.A, cpu->fetched_data);
            cpu->registers.A += cpu->fetched_data;
            // Set flags (z,n,h,c)!!!
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 0;
            cpu->flags.h = (carry && (1 >> 3));
            cpu->flags.c = (carry && (1 >> 7));
            printf("ADD A + %x = %x\n", cpu->fetched_data, cpu->registers.A);
            break;
        }
        case INS_ADC: {
            uint16_t carry = get_carry_add(cpu->registers.A + cpu->flags.c, cpu->fetched_data);
            cpu->registers.A += cpu->fetched_data + cpu->flags.c;
            // Set flags (z,n,h,c)!!!
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 0;
            cpu->flags.h = (carry && (1 >> 3));
            cpu->flags.c = (carry && (1 >> 7));
            printf("ADC + A %x = %x\n", cpu->fetched_data, cpu->registers.A);
            break;
        }
        case INS_ADD16: {
            uint16_t dest_reg = cpu_read_reg(cpu, cpu->cur_instruction.reg1);
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, dest_reg + cpu->fetched_data);
            uint16_t carry = get_carry_add(dest_reg, cpu->fetched_data);
            // Set flags based on carry vector result
            cpu->flags.n = 0;
            cpu->flags.h = (carry && (1 >> 11));
            cpu->flags.c = (carry && (1 >> 15));
            break;
        }
        case INS_SUB: {
            uint16_t carry = get_carry_add(cpu->registers.A, CA2(cpu->fetched_data));
            cpu->registers.A += CA2(cpu->fetched_data);
            // Set flags (z,n,h,c)!!!
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 1;
            cpu->flags.h = (carry && (1 >> 3));
            cpu->flags.c = (carry && (1 >> 7));
            printf("SUB A - %x = %x\n", cpu->fetched_data, cpu->registers.A);
            break;
        }
        case INS_SBC: {
            uint16_t carry = get_carry_add(cpu->registers.A, CA2(cpu->fetched_data) - cpu->flags.c);
            cpu->registers.A += CA2(cpu->fetched_data) - cpu->flags.c;
            // Set flags (z,n,h,c)!!!
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 1;
            cpu->flags.h = (carry && (1 >> 3));
            cpu->flags.c = (carry && (1 >> 7));
            break;
        }
        case INS_DAA: {
            // Decimal accumulator adjustor
            uint16_t offset = 0;
            if (cpu->registers.A & 0xF > 0x09 || cpu->flags.h) {
                offset |= 0x06;
            }
            if (cpu->registers.A > 0x99 || cpu->flags.c) {
                offset |= 0x60;
            }
            cpu->registers.A += offset;
            break;
        }
        case INS_DI: {
            cpu->ime = 0;
            break;
        }
        case INS_EI: {
            cpu->ime = 1;
            break;
        }
        case INS_CP: {
            uint16_t carry = get_carry_add(cpu->registers.A, CA2(cpu->fetched_data));
            uint8_t result = cpu->registers.A + CA2(cpu->fetched_data); // No update on register A
            // Set flags (z,n,h,c)!!!
            cpu->flags.z = (result == 0);
            cpu->flags.n = 1;
            cpu->flags.h = (carry && (1 >> 3));
            cpu->flags.c = (carry && (1 >> 7));
            printf("CP A - %2.2X = %2.2X\n", cpu->fetched_data, result);
            break;
        }
        case INS_AND: {
            // Perform AND operation between A register and specified register / data from memory
            // Store the result in the A register and set certain flags
            cpu->registers.A &= cpu->fetched_data;
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 0;
            cpu->flags.h = 1;
            cpu->flags.c = 0;
            break;
        }
        case INS_OR: {
            // Perform AND operation between A register and specified register / data from memory
            // Store the result in the A register and set certain flags
            cpu->registers.A |= cpu->fetched_data;
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 0;
            cpu->flags.h = 1;
            cpu->flags.c = 0;
            break;
        }
        case INS_XOR: {
            // Perform XOR operation between A register and specified register / data from memory
            // Store the result in the A register and set certain flags
            cpu->registers.A ^= cpu->fetched_data;
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 0;
            cpu->flags.h = 1;
            cpu->flags.c = 0;
            printf("XOR A %2.2X = %2.2X\n", cpu->fetched_data, cpu->registers.A);
            break;
        }
        case INS_STOP: {
            cpu->stopped = 1;
            break;
        }
        case INS_HALT: {
            cpu->halted = 1;
            break;
        }
        case INS_CCF: {
            // Flip the zero flag and clears N and H flags
            cpu->flags.n = 0;
            cpu->flags.h = 0;
            cpu->flags.z = ~cpu->flags.z;
            break;
        }
        case INS_CB: {
            // Prefix CB => look for next instruction
            cpu->cb_mode = true;
        }
        case INS_SCF: {
            // Set the carry flag and clears N and H flags
            cpu->flags.n = 0;
            cpu->flags.h = 0;
            cpu->flags.c = 1;
            break;
        }
        case INS_CPL: {
            // Complements the accumulator register and sets the N and H flags
            cpu->registers.A = ~cpu->registers.A;
            cpu->flags.n = 1;
            cpu->flags.h = 1;
            break;
        }
        case INS_RLC: {
            // Rotate Left Circular instruction
            cpu->flags.c = (cpu->fetched_data & 1 << 7);
            uint8_t res = (cpu->fetched_data << 1) + cpu->flags.c;
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            break;
        }
        case INS_RRC: {
            // Rotate Right Circular instruction
            cpu->flags.c = (cpu->fetched_data & 1 << 0);
            uint8_t res = (cpu->fetched_data >> 1) + (cpu->flags.c << 7);
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            break;
        }
        case INS_RL: {
            // Rotate Left with C flag as part of the register
            bool msb = (cpu->fetched_data & 1 << 7);
            uint8_t res = (cpu->fetched_data << 1)  + cpu->flags.c;
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            cpu->flags.c = msb;
            break;
        }
        case INS_RR: {
            // Rotate Right with C flag as part of the register
            bool lsb = (cpu->fetched_data & 1 << 0);
            uint8_t res = (cpu->fetched_data >> 1)  + (cpu->flags.c << 7);
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            cpu->flags.c = lsb;
            break;
        }
        case INS_SLA: {
            // Shift Left Arithmetically
            bool msb = cpu->fetched_data & (1 << 7);
            uint8_t res = cpu->fetched_data << 1;
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            cpu->flags.c = msb;
            cpu->flags.h = 0;
            cpu->flags.n = 0;
            cpu->flags.z = (res == 0);
            break;
        }
        case INS_SRA: {
            // Shift Right Arithmetically
            bool lsb = (cpu->fetched_data & 1 << 0);
            bool msb = (cpu->fetched_data & 1 << 7);
            uint8_t res = (cpu->fetched_data >> 1) | (msb << 7);
            cpu->flags.c = lsb;
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            break;
        }
        case INS_SRL: {
            // Shift Right Logically (ignore MSB)
            bool lsb = cpu->fetched_data & (1 << 0);
            uint8_t res = cpu->fetched_data >> 1;
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            cpu->flags.c = lsb;
            cpu->flags.n = 0;
            cpu->flags.h = 0;
            cpu->flags.z = (res == 0);
            break;
        }
        case INS_SWAP: {
            // Swap the first and last 4 bits of the 8 bits register
            uint8_t res = 0; 
            res |= cpu->fetched_data << 4;
            res |= cpu->fetched_data >> 4;
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, res, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, res);
            }
            cpu->flags.c = 0;
            cpu->flags.n = 0;
            cpu->flags.h = 0;
            cpu->flags.z = (res == 0);
            break;
        }
        case INS_BIT: {
            cpu->flags.z = cpu->fetched_data & (1 << cpu->cur_instruction.brs);
            cpu->flags.h = 1;
            cpu->flags.n = 0;
            break;
        }
        case INS_RES: {
            cpu->fetched_data &= ~(1 << cpu->cur_instruction.brs); 
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, cpu->fetched_data, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, cpu->fetched_data);
            }
            break;
        }
        case INS_SET: {
            cpu->fetched_data |= (1 << cpu->cur_instruction.brs); 
            if (cpu->is_dest_mem) {
                bus_write(cpu->mem_dest, cpu->fetched_data, cart);
            }
            else {
                cpu_write_reg(cpu, cpu->cur_instruction.reg1, cpu->fetched_data);
            }
            break;
        }
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
        fetch_instruction(cpu, cart);
        fetch_data(cpu, cart);
        execute_instruction(cpu, cart);
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
            return ~cpu->flags.z;
        case CT_C:
            return cpu->flags.c;
        case CT_NC:
            return ~cpu->flags.c;
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