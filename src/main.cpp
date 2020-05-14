#include <Arduino.h>
#include <FastLED.h>

boolean powerSave = false;
#define SHAKELIMIT 350
#define LED_PIN 13

#include "voltage.h"
#include "motion.h"
#include "led.h"


void setup() {
    setupMotion();
    setupLed();
    pinMode(LED_PIN, OUTPUT);    
}

// Beta 2

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

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
    shake = getMotion();
    /*
        Serial.print("shake : ");
        Serial.print(shake);
        */
    if(shake > SHAKELIMIT){
        powerSave = false;
    }else{
        LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);  
        //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_ON, TWI_OFF);        
    }
        // blinkState = !blinkState;
        // digitalWrite(LED_PIN, blinkState);

  }else{
    motionCheck++;
    motionCheck %= 5;
    if(motionCheck==0){
        shake = getMotion();
        if(shake>shakeaverage+9000){
            shake = shakeOld;
        }
    
//        Serial.print("shake : ");
        Serial.print(shake);
        Serial.print("\t");
//        Serial.print("\t avg : ");
        Serial.print(shakeaverage);
        Serial.print("\t");
        Serial.print((shake/shakeaverage)*1000);
        Serial.println("");
        if(shake > shakeaverage * 1.5+1000){
//            Serial.print("\t x");
            if(!shaken){
                shaking = true;
                shaken = true;
            }else{
                shaking = false;
            }
        }else{
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