#ifndef MIDI_H // prevent recursive inclusion
#define MIDI_H

#include <stdint.h>

// this midi device is always on channel 0

typedef enum {
//	STATE_IDLE,
	STATE_NOTE_ON_MESSAGE,
	STATE_READ_KEY,
	STATE_READ_VELOCITY,
	STATE_NOTE_OFF_KEY,
	STATE_NOTE_OFF_VELOCITY,
	STATE_PLAY_NOTE,
	STATE_CONTROL_CHANGE,
	STATE_CONTROLLER_NUMBER,
	STATE_MODULATION_CHANGE,
	STATE_PROGRAMMING

} message_state_t;

typedef enum {
	PASSCODE_NONE,
	PASSCODE_1,
	PASSCODE_2,
	PASSCODE_3,
	PROGRAMMING,
	RECORD_SCRATCH
} programming_state_t;

extern message_state_t state;
extern programming_state_t programming_state;

void MIDI_process(uint8_t byte1);

#endif
