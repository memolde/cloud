#pragma once
#include <Arduino.h>

#include <FastLED.h>

#define ANZAHL_LEDS 55
#define DATA_PIN 11
#define FRAMES_PER_SECOND  120
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

int promille = 0;
int brightnessold = 0;
CRGB leds[ANZAHL_LEDS];

void sky();
void fire2();


typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { fire2,  sky };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current


void setupLed() {
    //FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);   
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, ANZAHL_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps( 5, 100); //600 for Battery 200 for Programming
    FastLED.setBrightness(20);    
}
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);

}


void updateLed(float brightness ) {

  if(brightness>100 && brightnessold < 100){
    nextPattern();
  }
  brightnessold = brightness;

  // brightness = min(brightness * 4 ,255);

  // brightness = brightness * ANZAHL_LEDS / 255.0;
  /*
  Serial.print(" : ");
  Serial.print(brightness);
  Serial.print(" : ");
  */
 /*
  for (int i = 0; i < ANZAHL_LEDS -1 ; i++)
  {
    leds[i] = CRGB::Black;
    if((brightness+2>i) && ((brightness-2)<i) ){
      leds[i] = CRGB::Red;
    }
  }
  */

  
//  leds[0].nscale8(brightness);
  gPatterns[gCurrentPatternNumber]();
  FastLED.show();

  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
//  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS( 20 ) { 
    promille++; 
    promille = promille % 1000;
  } 
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


void colorBlob2(float center,float extend,CRGB color,CRGB subtract){
  center *=(float)ANZAHL_LEDS+extend*2.0;
  center -= extend;
  float from = center-extend;
  float to = center+extend;
  float distance = 0;
  for(int i = (int)from;i<=(int)to;i++){
    if(i>=0 && i<ANZAHL_LEDS){
      distance = extend - abs(( center - (float)i ) );
      float mult = distance / extend;
      if(mult<0){
        mult=0;
      }
      CRGB brighten = CRGB(color.red*mult,color.green*mult,color.blue*mult);
      CRGB darken = CRGB(subtract.red*mult,subtract.green*mult,subtract.blue*mult);
      leds[i] -= darken;
      leds[i] += brighten;
  #ifdef DEBUG
  Serial.print(distance / extend);
  Serial.print(brighten);
  Serial.println("");
  #endif
    }
  }
}


void colorBlob(float center,float extend,CRGB color){
  colorBlob2(center,extend,color,CRGB::Black);
};

void cloud(float position,float speed,float extend,boolean direction,CRGB color){

  if(direction == true){
    colorBlob((float)((int)(promille+position)%1000)/speed,extend,color);
  }else{
    colorBlob((float)((int)(1000-promille+position)%1000)/speed,extend,color);
  }
}

void sky(){
  fill_solid( leds, ANZAHL_LEDS, CRGB(10,20,200));  
  CRGB cloudcolor (220,210,50);
  cloud(200,400,2,true,cloudcolor);
  cloud(0,700,3,true,cloudcolor);
  cloud(100,1000,5,false,cloudcolor);
  cloud(800,600,4,false,cloudcolor);
}

void fire2(){
  int pulse = 50 + sin(promille*PI/250) * 15.0;
  CRGB firebase(255,pulse,0);
  fill_solid( leds, ANZAHL_LEDS, firebase);  
  CRGB firecolor (255,20+pulse,10);
  cloud(0,200,3,true,firecolor);
  cloud(200,300,4,true,firecolor);
  cloud(400,200,3,true,firecolor);
  cloud(600,250,4,true,firecolor);
  cloud(800,300,5,true,firecolor);
}
