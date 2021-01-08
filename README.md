# guitar-actuator
This is the codebase for the STM32 microcontrollers on the guitar actuator boards in the project Soundtrack. It's written in C and should be opened in STM32CubeIDE.
Codebase features:
- Written-from-scratch implementation of a subset of the MIDI protocol, featuring two layered state machines. It looks for MIDI note on messages recivied by the board.
- Servo control. If the board recives a MIDI on message for the MIDI note corresponding to this board, then we move the servo to strum the guitar.
- Persistent settings. The user can enter a "programming mode" and use the modulation knob on the MIDI keyboard to fine tune the servo positioning. These configs are then saved to flash and loaded upon boot.

For the designs of the board, see [here](https://github.com/lukeboi/guitar-board).
For an overview of Soundtrack as a whole, see [here](https://www.lukefarritor.com)

All rights reserved.
