#ifndef MIDI_H //prevent recursive inclusion
#define MIDI_H

#include <stdint.h>

//this midi device is always on channel 0, but we can change that later
//todo: see if this can be scoped better

int process_midi_message(uint8_t byte1);

#endif
