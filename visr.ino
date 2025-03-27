#include <FastLED.h>

#define LED_PIN A5
#define NUM_LEDS 161
#define LED_TYPE WS2812B
#define BRIGHTNESS 20

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(4.5, 500);
  FastLED.show();
}

void loop()
{
  uint_least8_t linePattern[NUM_LEDS] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
          6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
  };
  uint_least8_t lineColors[7] = { 0, 0, 1, 1, 1, 1, 1 };
  pattern(linePattern, lineColors, false, 1, 5);
}

void pattern(uint_least8_t pattern[NUM_LEDS], uint_least8_t patternColors[], bool reverse, float speed, uint_least8_t max) {
  uint_least8_t colors[2][3] = {
    {5, 160, 60},
    {0, 30, 170},
  };
  for (uint_least8_t x = 0; x < max; x++) {
    for (uint_least8_t z = 0; z < (4 * speed); z++) {
      for (uint_least8_t i = 0; i < NUM_LEDS; i++) {
        uint_least8_t color = (pattern[i] + x) % max;
        uint_least8_t colorA;
        uint_least8_t colorB;
        if (reverse) {
          colorB = (pattern[i] + (4 - x)) % max;
          colorA = (colorB + 1) % max;
        } else {
          colorA = (pattern[i] + x) % max;
          colorB = (colorA + 1) % max;
        }
        leds[i] = CRGB(
          getColorFade(colors[patternColors[colorA]][0], colors[patternColors[colorB]][0], z, (4 * speed)),
          getColorFade(colors[patternColors[colorA]][1], colors[patternColors[colorB]][1], z, (4 * speed)),
          getColorFade(colors[patternColors[colorA]][2], colors[patternColors[colorB]][2], z, (4 * speed))
        );
      }
      FastLED.show();
      FastLED.delay(50);
    }
  }
}

float getColorFade(uint_least8_t a, uint_least8_t b, uint_least8_t index, uint_least8_t range) {
  if (a == b)
  {
    return a;
  }
  float dif = abs(a - b);
  float change = dif / range;
  change *= (index + 1);
  if (a > b)
  {
    return a - change;
  }
  return a + change;
}