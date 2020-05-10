#include <Arduino.h>
#include <FastLED.h>

#include "motion.h"
#include "led.h"

void setup() {
    setupMotion();
    setupLed();
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
//    printMotion();
    updateLed();
    delay(500);
}