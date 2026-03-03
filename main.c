#include "emu.h"
#include "cart.h"
#include "cpu.h"

int main(int argc, char **argv) {
    // argc should be = 2 (program + rom path)
    // argv[1] contains path to rom
    return emu_run(argc, argv, &gb_cart, &gb_cpu);
}