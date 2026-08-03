#include "cpu.h"

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
            break;
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
            if (cpu_check_flag(cpu, cpu->cur_instruction.cond)) {
                cpu->registers.PC += e;
                printf("JR 0x%2.2x\n", cpu->registers.PC);
            }
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
            printf("DEC %s\n", reg_by_instruction(cpu->cur_instruction.reg1));
            cpu_write_reg16(cpu, cpu->cur_instruction.reg1, reg - 1);
            printf("BC = %2.2X\n", reg);
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
            ime_reg = false;
            cpu->ime = 0;
            printf("DI\n");
            break;
        }
        case INS_EI: {
            ime_reg = true;
            cpu->ime = 1;
            printf("EI\n");
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
            printf("AND %s\n", reg_by_instruction(cpu->cur_instruction.reg2));
            cpu->registers.A &= cpu->fetched_data;
            cpu->flags.z = (cpu->registers.A == 0);
            cpu->flags.n = 0;
            cpu->flags.h = 1;
            cpu->flags.c = 0;
            break;
        }
        case INS_OR: {
            // Perform OR operation between A register and specified register / data from memory
            // Store the result in the A register and set certain flags
            printf("A OR %s=%2.2X\n", reg_by_instruction(cpu->cur_instruction.reg2), cpu->fetched_data);
            cpu->registers.A |= cpu->fetched_data;
            cpu->flags.z = (cpu->registers.A == 0);
            printf("Z flag set to %d\n", cpu->flags.z);
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
            printf("XOR A 0x%2.2X = 0x%2.2X\n", cpu->fetched_data, cpu->registers.A);
            break;
        }
        case INS_STOP: {
            cpu->stopped = 1;
            break;
        }
        case INS_HALT: {
            cpu->halted = 1;
            printf("HALT\n");
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
            printf("PREFIX CB\n");
            cb = true;
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
            cpu->flags.z = ~(cpu->fetched_data & (1 << cpu->cur_instruction.brs));
            cpu->flags.h = 1;
            cpu->flags.n = 0;
            printf("BIT %d, %s\n", cpu->cur_instruction.brs, reg_by_instruction(cpu->cur_instruction.reg1));
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