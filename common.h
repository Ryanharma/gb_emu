#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "log.h"

#define BIT(a, n) ((a & (1 << n)) ? 1 : 0)
#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n);}
#define BETWEEN(a, b, c) ( (a >= b) && (a <= c))
#define ERROR(...) {log_fatal(__VA_ARGS__); exit(-1);}
