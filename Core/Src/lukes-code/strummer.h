#ifndef STRUMMER_H
#define STRUMMER_H

#include <stdint.h>

// Minimum period: 3278 - equivalent to 1ms
// Maximum period: 6557 - equivalent to 2ms

#define MINIMUM_PWM_POSITION 13000
#define MAXIMUM_PWM_POSITION 40000

void set_pulse(uint32_t p);
void strum();

#endif
