#include "interrupts.h"

gb_interrupt_t gb_interrupts = {0};

static const uint16_t interrupt_v[5] = {
    [0] = 0x40,
    [1] = 0x48,
    [2] = 0x50,
    [3] = 0x58,
    [4] = 0x60,
};

void interrupt_request(cpu_t *cpu, cart_t *cart, gb_interrupt_t *gb_interrupts) {
    // CPU is checking for pending interrupts (during halt mode)
    for (int i = 0; i < 5; i++) {
        // Check for each bit (used) of the 8-bit registers IE and IF
        if ((gb_interrupts->IE & 1 << i) && (gb_interrupts->IF & 1 << i)) {
            if (cpu->ime)
                // If ime flag is set, the interrupt is handled
                interrupt_handle(cpu, cart, gb_interrupts);
            break;
        }
    }
}
void interrupt_handle(cpu_t *cpu, cart_t *cart, gb_interrupt_t *gb_interrupts) {
    // CPU is serving an interrupt (requested by IF register)

    cpu->ime = 0; // Set ime flag to 0 so that only one interrupt is handled at a time

    // Step 1: Push into the stack the current value of the PC register (2 M-cycles bc 2 bytes)
    cpu->registers.PC--; // Because it was incremented before the interrupt handle
    cpu->registers.SP--;
    bus_write(cpu->registers.SP, cpu->registers.PC >> 8, cart);
    cpu->registers.SP--;
    bus_write(cpu->registers.SP, cpu->registers.PC & 0xFF, cart);

    // Step 2: Set PC value to address depending on the interrupt (priority to the LSBs)
    for (int i = 0; i < 5; i++) {
        // Check for each bit of the 8-bit registers IE and IF
        if ((gb_interrupts->IE & 1 << i) && (gb_interrupts->IF & 1 << i)) {
            cpu->registers.PC = interrupt_v[i];
            break;
        }
    }
}