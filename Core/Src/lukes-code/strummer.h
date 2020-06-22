#ifndef STRUMMER_H //prevent recursive inclusion
#define STRUMMER_H

//#include "stm32l4xx_hal_def.h"

//a difference of 8 is a good starting point
//23 = all the way over/right


#define STRUMMED_OFF_POSITION 15
#define STRUMMED_ON_POSITION 16

//#define STRUMMED_OFF_POSITION 12
//#define STRUMMED_ON_POSITION 16//23


void passServoPWM(s);

void STRUMMER_strum();

#endif
