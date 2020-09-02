# guitar-actuator
This is the codebase for the STM32 microcontrollers on the guitar actuator boards in the project Soundtrack. It's written in C and should be opened in STM32CubeIDE.
Codebase features:
- Very simple written-from-scratch implementation of the MIDI protocol. It looks for MIDI note on messages recivied by the board.
- Servo control. If the board recives a MIDI on message for the MIDI note corresponding to this board, then we move the servo to strum the guitar.

For the designs of the board, see [here](https://github.com/lukeboi/guitar-board).
For an overview of Soundtrack as a whole, see [here](https://www.lukefarritor.com)

Note to self: you should someday move the customizable stuff to a single file instead of two.
