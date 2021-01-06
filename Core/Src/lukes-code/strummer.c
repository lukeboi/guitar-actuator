#include "strummer.h"
#include "./main.h"

int is_flipped = 0;
TIM_HandleTypeDef * servoPWM; //pwm controller of the servo

//code used to set PWM pulse. parts of this function were copied from auto-generated STM32 code setup
void set_pulse(int p) {
	TIM1->CCR2 = p;
//    TIM_OC_InitTypeDef sConfigOC = {0};
//    sConfigOC.OCMode = TIM_OCMODE_PWM1;
//    sConfigOC.Pulse = p;
//    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
//    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
//    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
//    if (HAL_TIM_PWM_ConfigChannel(&servoPWM, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
//        Error_Handler();
//    }
//    HAL_TIM_PWM_Start(&servoPWM, TIM_CHANNEL_2);


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

void pass_servo_pwm(TIM_HandleTypeDef *s) { //used when the system is being initalized to pass the servo pwm controller. Todo: change to extern statement
    servoPWM = s->Instance;
}
