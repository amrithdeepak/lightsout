#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "lib/boardutil.h"
#include "lib/contracts.h"

bitarray bitarray_new() {
    bitarray i = 0;
    return i;
}

bool bitarray_get(bitarray n, uint8_t i) {
    REQUIRES (i < BITARRAY_LIMIT);
    return (((n>>i) & 0x01) == 1);
    
}

bitarray bitarray_flip(bitarray n, uint8_t i) {
    REQUIRES (i < BITARRAY_LIMIT);
    return (n^(1<<i));
}
