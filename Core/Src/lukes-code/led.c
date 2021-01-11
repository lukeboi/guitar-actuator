#include "./main.h"

/*
 * led.c
 *
 *  Created on: Jan 10, 2021
 *      Author: lfarritor3
 */

// Turns LED off on board
void led_on() {
	  HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
}

// Turns LED on on board
void led_off() {
	  HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
}

// Toggles debug LED on board
void toggle_led() {
	HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
}

// Blinks debug LED a given number of times
void blink(int x) {
	for(int i = 0; i < x * 2; i++) {
		toggle_led();
		HAL_Delay(100);
	}
}
