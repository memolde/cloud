#include <Arduino.h>

#include "motion.h"
#include "led.h"

void setup() {
    setupMotion();
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    printMotion();
    delay(500);
}