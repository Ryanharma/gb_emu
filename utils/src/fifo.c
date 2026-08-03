#include "fifo.h"

// fifo_t init_fifo() {
//     fifo_t fifo;
//     fifo->fifo_ptr = 0;
//     return fifo;
// }

void clear_fifo(fifo_t *fifo) {
    // Clear FIFO doesn't actually clear the memory, just reset the pointer
    fifo->fifo_ptr = 0;
}

bool is_empty(fifo_t *fifo) {
    if (fifo->fifo_ptr == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool is_full(fifo_t *fifo) {
    if (fifo->fifo_ptr == FIFO_SIZE) {
        return true;
    }
    else {
        return false;
    }
}

void push(fifo_t *fifo, pixel_t pixel) {
    if (!is_full(fifo)) {
        fifo->fifo_mem[fifo->fifo_ptr] = pixel;
        fifo->fifo_ptr++;
    }
    else {
        ERROR("FIFO is full");
    }

}

pixel_t pop(fifo_t *fifo) {
    if (!is_empty(fifo)) {
        fifo->fifo_ptr--;
        pixel_t pixel = fifo->fifo_mem[fifo->fifo_ptr];
        return pixel;
    }
    else {
        ERROR("FIFO is empty");
    }
}