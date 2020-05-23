#ifndef STRUMMER_H //prevent recursive inclusion
#define STRUMMER_H

//#include "stm32l4xx_hal_def.h"

#define STRUMMED_OFF_POSITION 6
#define STRUMMED_ON_POSITION 10

void passServoPWM(s);

void STRUMMER_strum();

#endif
