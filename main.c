#include "emu.h"
#include "cart.h"

cart_t cart = {0};
cpu_t cpu = {0};
int main(int argc, char **argv) {
    return emu_run(argc, argv, &cart, &cpu);
}