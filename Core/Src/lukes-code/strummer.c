#include <stdbool.h>
#include "strummer.h"
#include "config.h"
#include "./main.h"

bool is_flipped = false;

// Sets servo PWM pulse
void set_pulse(uint32_t p) {
	TIM1->CCR2 = p;
}

// Moves the servo across the guitar strings once
void strum() {
    if(is_flipped == false) {
        set_pulse(ram_config.strummed_on_position);
        is_flipped = true;
    }
    else {
        set_pulse(ram_config.strummed_off_position);
        is_flipped = false;
    }
}

//void pass_servo_pwm(TIM_HandleTypeDef *s) { //used when the system is being initalized to pass the servo pwm controller. Todo: change to extern statement
//    servoPWM = s->Instance;
//}
