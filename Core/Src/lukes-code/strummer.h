#ifndef STRUMMER_H //prevent recursive inclusion
#define STRUMMER_H

// Minimum period: 3278 - equivalent to 1ms
// Maximum period: 6557 - equivalent to 2ms

#define STRUMMED_OFF_POSITION 3278
#define STRUMMED_ON_POSITION 6557

void passServoPWM(s);

void STRUMMER_strum();

#endif
