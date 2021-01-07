#include "strummer.h"
#include "./main.h"

int is_flipped = 0;

void set_pulse(int p) {
	TIM1->CCR2 = p;
}

void strum() {
    if(is_flipped == 0) {
        set_pulse(STRUMMED_ON_POSITION);
        is_flipped = 1;
    }
    else {
        set_pulse(STRUMMED_OFF_POSITION);
        is_flipped = 0;
    }
}

//void pass_servo_pwm(TIM_HandleTypeDef *s) { //used when the system is being initalized to pass the servo pwm controller. Todo: change to extern statement
//    servoPWM = s->Instance;
//}
