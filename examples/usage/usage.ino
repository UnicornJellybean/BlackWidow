// Example usage for Wire library by Jonathan BAUDIN, Thibaut VIARD, Arduino.

#include "Wire.h"

// Initialize objects from the lib
Wire wire;

void setup() {
    // Call functions on initialized library objects that require hardware
    wire.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    wire.process();
}
