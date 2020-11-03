#include "midi.h"
#include "stm32f0xx_hal.h"

int CURRENT_STATUS = 0;
int note = 41; //what note on the keyboard we should respond to. Each guitar is one note. note 69 = A4 = the A above middle C

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

extern UART_HandleTypeDef huart1;

//processes a MIDI message. we return a 1 if we need to strum. Some messages can be 2 bytes, so the third byte might just be 0x0.
int process_midi_message(uint8_t byte1) { //TODO: later change this to array


	if(byte1 >= 128) { //check to see if the first bit of the first byte this means that its a system message and we need to switch to that status
        CURRENT_STATUS = byte1; //unused for now

        switch (byte1) { //now, interpret the message itself
        case STATUS_NOTE_ON:
        	return note_on();
            break;

        case STATUS_NOTE_OFF:
            return note_off();
            break;

        case STATUS_AFTERTOUCH:
            return 0;
            break;

        case STATUS_CONTROL_CHANGE:
            return 0;
            break;

        case STATUS_PROGRAM_CHANGE:
            return 0;
            break;

        case STATUS_CHANNEL_PRESSURE:
            return 0;
            break;

        case STATUS_PITCH_BEND:
            return 0;
            break;

        default:
            return 0;
            break;
        }
    }
    else {
        //if the first byte isn’t a status byte, then we are in the previous status. aka running status. depending on current status
        switch(CURRENT_STATUS) {
        case STATUS_NOTE_ON:
            return note_on();
            break;

        case STATUS_NOTE_OFF:
            return note_off();
            break;

        default:
            return 0;
        }
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
	if(a == note) {
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
