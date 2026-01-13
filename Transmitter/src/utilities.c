#include <stdint.h>
#include "utilities.h"
#include "timer.h"


void delay(uint32_t microseconds) {
    uint64_t start_time = getTicks();
    uint64_t end_time = start_time + microseconds;
    
    while (getTicks() < end_time) {
    }
}