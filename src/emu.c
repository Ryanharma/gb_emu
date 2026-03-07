#include "emu.h"

// This file is required to group every component of the SOC to build the emulator

/* The emulator consist of 
--------- CPU  --------
--------- Cart --------
----- Address Bus -----
--------- PPU ---------
-------- Timer -------
*/

static emu_t emu = {0};

void emu_cycles(int cpu_cycles){
    // Represent one machine cycle
    // SDL_Delay(4*1/CLK_CYCLE);
    return;
}

int emu_run(int argc, char **argv, cart_t *cart, cpu_t *cpu) {
    if (argc < 2) {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argv[1], cart)) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded..\n");

    cpu_init(cpu);
    
    emu.running = true;
    emu.paused = false;
    emu.ticks = 0;
    int i = 0;
    while(emu.running) {
        if (emu.paused) {
            // delay(10);
            continue;   
        }

        if (!cpu_step(cpu, cart)) {
            printf("CPU Stopped\n");
            return -3;
        }
        if (i>20) {
            ERROR("ONLY DO 20 EXEC");
        }
        // print_cpu_state(cpu);
        emu.ticks++;
        i++;
    }

    return 0;
}