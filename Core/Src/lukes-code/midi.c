#include "led.h"
#include "midi.h"
#include "config.h"
#include "strummer.h"
#include "stm32f0xx_hal.h"

int CURRENT_STATUS = 0;

//notes for use in programming mode
#define PROGRAMMING_MODE_PASSCODE_1 24
#define PROGRAMMING_MODE_PASSCODE_2 22
#define PROGRAMMING_MODE_PASSCODE_3 23
#define PROGRAMMING_MODE_PASSCODE_4 21
#define PROGRAMMING_MODE_SAVE_LEFT_POS 25
#define PROGRAMMING_MODE_SAVE_CHANGES 26
#define PROGRAMMING_MODE_SAVE_RIGHT_POS 27

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

message_state_t state;
programming_state_t programming_state;

uint_fast8_t recived_key;
uint_fast8_t recived_velocity;
uint_fast8_t recived_control_number;
uint_fast8_t recived_modulation;
uint_fast8_t record_scratch_pulse;

extern UART_HandleTypeDef huart1;
extern config_t config;

static void _process_programming_state(uint8_t note);

int read_key_num = 0;

// Processes MIDI messages using a state machine
void MIDI_process(uint8_t byte1) {
	if(byte1 & 0x80) { //check to see if the first bit of the first byte is 1. this means that its a system message and we need to switch to that status
        CURRENT_STATUS = byte1; //unused for now

        switch (byte1) { //now, interpret the message itself
        case STATUS_NOTE_ON:
        	state = STATE_READ_KEY;
            break;

        case STATUS_NOTE_OFF:
//        	state = STATE_NOTE_OFF_READ_KEY;
            break;

        case STATUS_AFTERTOUCH:
            break;

        case STATUS_CONTROL_CHANGE:
        	state = STATE_CONTROL_CHANGE;
            break;

        case STATUS_PROGRAM_CHANGE:
            break;

        case STATUS_CHANNEL_PRESSURE:
            break;

        case STATUS_PITCH_BEND:
            break;

        case 254: // Active sensing
//        	state = STATE_IDLE;
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

//        case STATE_NOTE_OFF_READ_KEY:
//        	state = STATE_NOTE_OFF_READ_VELOCITY;
//        	break;

//        case STATE_NOTE


        case STATE_READ_VELOCITY:
        	recived_velocity = byte1;
        	if (recived_key == ram_config.note && recived_velocity > 0) {
            	read_key_num += 1;
        		state = STATE_PLAY_NOTE;
        	}
        	else {
        		state = STATE_READ_KEY;
        	}

        	if(recived_velocity > 0) {
        		_process_programming_state(recived_key);
        	}
    		break;

        case STATE_CONTROL_CHANGE:
        	recived_control_number = byte1;
        	if(recived_control_number == 1) {
        		state = STATE_MODULATION_CHANGE;
        	}
        	break;

        case STATE_MODULATION_CHANGE:
        	recived_modulation = byte1;
        	if(programming_state == RECORD_SCRATCH) {
        		record_scratch_pulse = ((MAXIMUM_PWM_POSITION - MINIMUM_PWM_POSITION) * recived_modulation) / 128 + MINIMUM_PWM_POSITION;
        		set_pulse(record_scratch_pulse);
        	}
        	break;

        default:
        	break;
        }
    }
}

// State machine for programming state (programming state is for changing paramaters in flash)
void _process_programming_state(uint8_t note) {
	// TODO move these magic numbers to another location
	switch(programming_state) {
	case PASSCODE_NONE:
		if (note == PROGRAMMING_MODE_PASSCODE_1) {
			programming_state = PASSCODE_1;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PASSCODE_1:
		if (note == PROGRAMMING_MODE_PASSCODE_2) {
			programming_state = PASSCODE_2;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PASSCODE_2:
		if (note == PROGRAMMING_MODE_PASSCODE_3) {
			programming_state = PASSCODE_3;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PASSCODE_3:
		if (note == PROGRAMMING_MODE_PASSCODE_4) {
			programming_state = PROGRAMMING;
			state = STATE_PROGRAMMING;
			led_on();
			blink(2);
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case PROGRAMMING:
		if (note == ram_config.note) {
			programming_state = RECORD_SCRATCH;
		}
		else {
			programming_state = PASSCODE_NONE;
			led_off();
		}
		break;
	case RECORD_SCRATCH:
		if (note == PROGRAMMING_MODE_SAVE_LEFT_POS) {
			ram_config.strummed_off_position = record_scratch_pulse;
		}
		else if (note == PROGRAMMING_MODE_SAVE_RIGHT_POS) {
			ram_config.strummed_on_position = record_scratch_pulse;
		}
		else if (note == PROGRAMMING_MODE_SAVE_CHANGES) {
			Write_Flash();
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;

    default:
    	break;
	}
}
