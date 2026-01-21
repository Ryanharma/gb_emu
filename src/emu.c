#include "emu.h"

// This file is required to group every component of the SOC to build the emulator

/* The emulator consist of 
--------- CPU  --------
--------- Cart --------
----- Address Bus -----
--------- PPU ---------
-------- Timer -------
*/

static emu_t emu;

void emu_cycles(int cpu_cycles){
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

    // SDL_Init(SDL_INIT_VIDEO);
    // printf("SDL INIT\n");
    // TTF_Init();
    // printf("TTF INIT\n");

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
        if (i>10) {
            ERROR("ONLY DO 1 EXEC");
        }
        emu.ticks++;
        i++;
    }

    return 0;
}