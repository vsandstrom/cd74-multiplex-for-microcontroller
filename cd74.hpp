#include "core_pins.h"

/*
io: microcontroller pin for input/output.
mode: 0 for input, 1 for output.
sw1, sw2, sw3: pins for choosing which gate in multiplexer to read/write from.
enable: turns the multiplexer on with a LOW or 0 signal.

Multiplex .read() function should be called after a small delay, letting the signal 
stabilize while transmitted through the multiplexer.
*/

class Multiplex {
  private:
    int io;
    int mode;
    int sw1, sw2, sw3;
    int enable;

    /// Binary encoding
    ///__________________________________
    ///|  1.  |  2.  |  3.  |    I/O    |
    ///|______|______|______|___________|
    ///|  LOW |  LOW |  LOW | 0 active. |
    ///| HIGH |  LOW |  LOW | 1 active. |
    ///|  LOW | HIGH |  LOW | 2 active. |
    ///| HIGH | HIGH |  LOW | 3 active. |
    ///|  LOW |  LOW | HIGH | 4 active. |
    ///| HIGH |  LOW | HIGH | 5 active. |
    ///|  LOW | HIGH | HIGH | 6 active. |
    ///| HIGH | HIGH | HIGH | 7 active. |
    ///|______|______|______|___________|

    // Hard-coded pattern 
    int sw1_pattern[8] = {0, 1, 0, 1, 0, 1, 0, 1};
    int sw2_pattern[8] = {0, 0, 1, 1, 0, 0, 1, 1};
    int sw3_pattern[8] = {0, 0, 0, 0, 1, 1, 1, 1};
  
  public:
    Multiplex(int io, int mode, int sw1, int sw2, int sw3, int enable);
    void gate(unsigned int gate_num);
    void output_off(); 
    void output_on();
    void initialize();
    int input_read();
};

