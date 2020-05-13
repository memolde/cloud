#include <Arduino.h>
#include <FastLED.h>

boolean powerSave = false;

#include "voltage.h"
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
int shake = 0;
long vcc = 0;

void loop() {

  if(powerSave){
        shake = getMotion();
  }else{
    motionCheck++;
    motionCheck %= 30;
    if(motionCheck==0){
        shake = getMotion();
        Serial.print("shake : ");
        Serial.print(shake);
        vcc = readVcc();
        Serial.print("voltage : ");
        Serial.println(vcc);

    }
/*
    float shake = printMotion();
    Serial.print("shake : ");
    Serial.print(shake);
    Serial.print("\t");
    int bright = sqrt(shake);
    */
    updateLed(shake);
  }
}