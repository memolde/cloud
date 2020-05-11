#pragma once
#include <Arduino.h>

#include <FastLED.h>

#define ANZAHL_LEDS 26
#define DATA_PIN 11
#define FRAMES_PER_SECOND  30
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

int promille = 0;
int brightnessold = 0;
CRGB leds[ANZAHL_LEDS];

void sky();
void fire2();
void rainbow();
void thunderstorm();

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { thunderstorm, fire2,  sky, rainbow };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current


void setupLed() {
    //FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);   
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, ANZAHL_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps( 5, 200); //600 for Battery 200 for Programming
    FastLED.setBrightness(90);    
}
void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);

}


void updateLed(float brightness ) {

  if(brightness>150 && brightnessold < 150){
    nextPattern();
  }
  brightnessold = brightness;
  
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
void rainbow(){
  uint8_t hue;
  hue = long(promille)*250L/1000L;
  for( uint16_t i = 0; i < ANZAHL_LEDS; i++) {
    leds[i] = CHSV(hue,255,255);
    hue += 256/ANZAHL_LEDS;
  }
}
void thunderstorm(){
  fill_solid( leds, ANZAHL_LEDS, CRGB(10,0,150));  
  CRGB cloudcolor (50,0,100);
  cloud(200,400,2,true,cloudcolor);
  cloud(0,700,3,true,cloudcolor);
  cloud(100,1000,5,false,cloudcolor);
  cloud(800,600,4,false,cloudcolor);
  switch (promille)
  {
  case 100:
    fill_solid( leds, ANZAHL_LEDS, CRGB(255,100,255));  
    break;
  case 300:
    fill_solid( leds, ANZAHL_LEDS, CRGB(200,100,255));  
    break;
  case 460:
    fill_solid( leds, ANZAHL_LEDS, CRGB(255,100,180));  
    break;
  case 490:
    fill_solid( leds, ANZAHL_LEDS, CRGB(255,100,180));  
    break;
  case 730:
    fill_solid( leds, ANZAHL_LEDS, CRGB(200,100,255));  
    break;
  case 890:
    fill_solid( leds, ANZAHL_LEDS, CRGB(255,100,200));  
    break;
  case 980:
    fill_solid( leds, ANZAHL_LEDS, CRGB(255,100,200));  
    break;
  
  default:
    break;
  }
}