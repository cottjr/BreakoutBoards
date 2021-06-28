// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN 6
#define N_LEDS 24

// Traditional RGB strip usage
// Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// For RGBW strips like the https://www.adafruit.com/product/2862
//  NeoPixel Ring - 24 x 5050 RGBW LEDs w/ Integrated Drivers - Natural White - ~4500K
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup()
{
  strip.begin();
}

void loop()
{
  chase(strip.Color(35, 0, 0)); // Red
  delay(250);
  chase(strip.Color(0, 35, 0)); // Green
  delay(250);
  chase(strip.Color(0, 0, 35)); // Blue
  delay(250);
  chase(strip.Color(30, 30, 30)); // Fake White
  delay(250);
  chase(strip.Color(0, 0, 0, 25)); // Pure White
  delay(250);}

static void chase(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++)
  {
    strip.setPixelColor(i, c);     // Draw new pixel
    strip.setPixelColor(i - 4, 0); // Erase pixel a few steps back
    strip.show();
    delay(20);
  }
}