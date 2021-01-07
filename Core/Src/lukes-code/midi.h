#ifndef MIDI_H //prevent recursive inclusion
#define MIDI_H

#include <stdint.h>

//this midi device is always on channel 0, but we can change that later
//todo: see if this can be scoped better

int process_midi_message(uint8_t byte1);

typedef enum {
	STATE_IDLE,
	STATE_NOTE_ON_MESSAGE,
	STATE_READ_KEY,
	STATE_READ_VELOCITY,
	STATE_PLAY_NOTE,
	STATE_PROGRAMMING

} message_state_t;

typedef enum {
	PASSCODE_NONE,
	PASSCODE_1,
	PASSCODE_2,
	PASSCODE_3,
	PROGRAMMING
} programming_state_t;

extern message_state_t state;
extern programming_state_t programming_state;

#endif
