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

int motionCheck = 0;
int bright = 0;

void loop() {
    motionCheck++;
    motionCheck %= 30;
    if(motionCheck==0){
        bright = getMotion();
    }

/*
    float shake = printMotion();
    Serial.print("shake : ");
    Serial.print(shake);
    Serial.print("\t");
    int bright = sqrt(shake);
    */
    updateLed(bright);
}