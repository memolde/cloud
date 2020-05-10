#include <Arduino.h>

#include <FastLED.h>

#define ANZAHL_LEDS 5
#define DATA_PIN 11
CRGB leds[ANZAHL_LEDS];

void setupLed() {
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, ANZAHL_LEDS);
}

void updateLed() {
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
}
