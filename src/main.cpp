#include <Arduino.h>
#include <FastLED.h>

boolean powerSave = false;
#define SHAKELIMIT 350
#define LED_PIN 13

#include "voltage.h"
#include "motion.h"
#include "led.h"

boolean shakeDetection();

void setup() {
    setupMotion();
    setupLed();
    pinMode(LED_PIN, OUTPUT);    
}

// Beta 2 Release 1.0

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================
int updateRate = 20;
int motionCheck = 0;
float shake = 0;
float shakeOld = 0;
float shakeaverage = 5000;
long vcc = 0;
bool blinkState = false;
boolean shaken = false;
boolean shaking = false;

void loop() {

  if(powerSave){
    
    if(shakeDetection()){
        powerSave = false;
        resetLEDState();
        // No pattern change
        shaking = false;
    }else{
        LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);  
        updateLed(shaking);
    }
  }else{
    motionCheck++;
    motionCheck %= updateRate;
    if(motionCheck==0){
        shakeDetection();
    }
/*
    float shake = printMotion();
    Serial.print("shake : ");
    Serial.print(shake);
    Serial.print("\t");
    int bright = sqrt(shake);
    */
    updateLed(shaking);
    shaking = false;
  }
}
boolean shakeDetection(){
    shake = getMotion();
    // Filter extremes
    if(shake>shakeaverage+9000){
        shake = shakeOld;
    }

    //        Serial.print("shake : ");
    Serial.print(shake);
    Serial.print("\t");
    //        Serial.print("\t avg : ");
    Serial.print(shakeaverage);
    Serial.print("\t");
    //        Serial.print((shake/shakeaverage)*1000);
    Serial.println("");

    if(shake > shakeaverage * 1.3+1000){
        if(!shaken){
            shaking = true;
            shaken = true;
            updateRate=50;
            shakeaverage=shake;
        }else{
            shaking = false;
        }
    }else{
        updateRate -=5;
        updateRate = max(updateRate,10);
        shaken = false;
        shaking = false;
    }
    // Serial.print("\t ");
    // Serial.println(shaking);
    /*
    vcc = readVcc();
    Serial.print("voltage : ");
    Serial.println(vcc);
    */
    if(shakeaverage > shake ){
            shakeaverage = ( shakeaverage * 9 + shake )/10;
    }else{
            shakeaverage = ( shakeaverage * 1 + shake )/2;
    }
    shakeOld = shake;
    return shaking;
}