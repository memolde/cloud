#include <Arduino.h>
#include <FastLED.h>

boolean powerSave = false;
#define SHAKELIMIT 250
#define LED_PIN 13

#include "voltage.h"
#include "motion.h"
#include "led.h"


void setup() {
    setupMotion();
    setupLed();
    pinMode(LED_PIN, OUTPUT);    
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

int motionCheck = 0;
int shake = 0;
long vcc = 0;
bool blinkState = false;

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
    motionCheck %= 30;
    if(motionCheck==0){
        shake = getMotion();
    /*
        Serial.print("shake : ");
        Serial.print(shake);
        vcc = readVcc();
        Serial.print("voltage : ");
        Serial.println(vcc);
    */
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