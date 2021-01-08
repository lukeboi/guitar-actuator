#include "midi.h"
#include "config.h"
#include "strummer.h"
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

message_state_t state;
programming_state_t programming_state;

uint_fast8_t recived_key;
uint_fast8_t recived_velocity;
uint_fast8_t recived_control_number;
uint_fast8_t recived_modulation;
uint_fast8_t record_scratch_pulse;

extern UART_HandleTypeDef huart1;
extern config_t config;

void process_programming_state(uint8_t note);

//processes a MIDI message
void process_midi_message(uint8_t byte1) { //TODO: later change this to array
	if(byte1 & 0x80) { //check to see if the first bit of the first byte this means that its a system message and we need to switch to that status
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
        	state = STATE_CONTROL_CHANGE;
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
	case PROGRAMMING:
		if (note == ram_config.note) {
			programming_state = RECORD_SCRATCH;
		}
		else {
			programming_state = PASSCODE_NONE;
		}
		break;
	case RECORD_SCRATCH:
		if (note == 77) {
			ram_config.strummed_off_position = record_scratch_pulse;
		}
		else if (note == 79) {
			ram_config.strummed_on_position = record_scratch_pulse;
		}
		else if (note == 84) {
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
