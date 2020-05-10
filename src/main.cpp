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
/*
    float shake = printMotion();
    Serial.print("shake : ");
    Serial.print(shake);
    Serial.print("\t");
    int bright = sqrt(shake);
    */
    int bright = 100;
    updateLed(bright);
}