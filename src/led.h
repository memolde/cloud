#pragma once
#include <Arduino.h>

#include <FastLED.h>

#define ANZAHL_LEDS 25
#define DATA_PIN 11
CRGB leds[ANZAHL_LEDS];

void setupLed() {
    //FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);   
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, ANZAHL_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps( 5, 200); //600 for Battery 200 for Programming
    FastLED.setBrightness(80);    
}

void updateLed(float brightness ) {

  brightness = min(brightness * 4 ,255);

  brightness = brightness * ANZAHL_LEDS / 255.0;
  Serial.print(" : ");
  Serial.print(brightness);
  Serial.print(" : ");
  for (int i = 0; i < ANZAHL_LEDS -1 ; i++)
  {
    leds[i] = CRGB::Black;
    if((brightness+2>i) && ((brightness-2)<i) ){
      leds[i] = CRGB::Red;
    }
    /* code */
  }
  
//  leds[0].nscale8(brightness);
  FastLED.show();

  /*
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Yellow;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
  */
}
