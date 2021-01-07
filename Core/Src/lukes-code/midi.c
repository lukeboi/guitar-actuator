#include "midi.h"
#include "config.h"
#include "stm32f0xx_hal.h"

int CURRENT_STATUS = 0;

//note control
#define STATUS_NOTE_ON 0b10010000
#define STATUS_NOTE_OFF 0b10000000

//other midi status bytes
#define STATUS_AFTERTOUCH 0b10100000
#define STATUS_CONTROL_CHANGE 0b10110000
#define STATUS_PROGRAM_CHANGE 0b11000000
#define STATUS_CHANNEL_PRESSURE 0b11010000
#define STATUS_PITCH_BEND 0b11100000

//system message
#define STATUS_SYSTEM 0xF;

int note_on();
int note_off();
uint8_t get_one_byte();

message_state_t state;
programming_state_t programming_state;

uint8_t recived_key;
uint8_t recived_velocity;

extern UART_HandleTypeDef huart1;
extern config_t config;


//processes a MIDI message. we return a 1 if we need to strum. Some messages can be 2 bytes, so the third byte might just be 0x0.
int process_midi_message(uint8_t byte1) { //TODO: later change this to array
	if(byte1 >= 128) { //check to see if the first bit of the first byte this means that its a system message and we need to switch to that status
        CURRENT_STATUS = byte1; //unused for now

        switch (byte1) { //now, interpret the message itself
        case STATUS_NOTE_ON:
        	state = STATE_READ_KEY;
            break;

        case STATUS_NOTE_OFF:
            break;

        case STATUS_AFTERTOUCH:
            break;

        case STATUS_CONTROL_CHANGE:
            break;

        case STATUS_PROGRAM_CHANGE:
            break;

        case STATUS_CHANNEL_PRESSURE:
            break;

        case STATUS_PITCH_BEND:
            break;

        default:
            break;
        }
    }
    else {
        //if the first byte isn’t a status byte, then we are in the previous status. aka running status. depending on current status
        switch(state) {
        case STATE_READ_KEY:
        	recived_key = byte1;
        	state = STATE_READ_VELOCITY;
        	break;

        case STATE_READ_VELOCITY:
        	recived_velocity = byte1;
        	if (recived_key == ram_config.note && recived_velocity > 0) {
        		state = STATE_PLAY_NOTE;
        	}
        	else {
        		state = STATE_IDLE;
        	}
    		process_programming_state(recived_key);
        }
    }
}

// State machine for programming state (programming state is for changing paramaters in flash)
void process_programming_state(uint8_t note) {
	switch(programming_state) {
	case PASSCODE_NONE:
		if (note == 84) {
			programming_state = PASSCODE_1;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PASSCODE_1:
		if (note == 82) {
			programming_state = PASSCODE_2;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PASSCODE_2:
		if (note == 83) {
			programming_state = PASSCODE_3;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PASSCODE_3:
		if (note == 81) {
			programming_state = PROGRAMMING;
			state = STATE_PROGRAMMING;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	}
}

uint8_t get_one_byte() {
	uint8_t b;
	HAL_UART_Receive(&huart1, &b, 1, HAL_MAX_DELAY);
	return b;
}

int note_on() {
	uint8_t a = get_one_byte();
	uint8_t b = get_one_byte();
	if(a == config.note) {
		if(b != 0) {
			return 1;
		}
	}
	return 0;
}

int note_off() {
	get_one_byte();
	get_one_byte();
}
