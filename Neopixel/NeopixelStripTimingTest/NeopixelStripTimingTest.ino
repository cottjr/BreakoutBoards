// This sample exists to
//  explore the timing required to update different neopixels
//  e.g. what is the timing?
//  e.g. does the timing vary from the 1st pixel to the last pixel in the strip?
//  e.g. does the timing vary if you update just one pixel versus all pixels in the srip?

// Findings
//  240 micro-seconds to write all pixels for a string of 8
//  120 micro-seconds to write all pixels for a string of 4
//  each bit seems to be about 1.25 micro-seconds
//  and some time is need to latch values before you can send another color value update to the strip
// Net Result -> Design Pattern
//  use strip.setPixelColor(i, c) to set the gamma corrected color value in RAM for each pixel you want to update
//  then use strip.show() to cause the entire strip to be written to
//  => if you do NOT change the value of a pixel since the last .show(), the prior value persists/ will be written
// Rember that color values consume RAM ~ 3 bytes for each pixel
//  nothing to worry about for short strips
//  but can add up quickly if you have larger matrices

// Reference from original Adafruit NeopixelStripTest sample
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
#define N_LEDS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
}

void loop()
{
  uint16_t i = N_LEDS-1;
  setPixel(i, strip.Color(35, 0, 0));
  setPixel(i-1, strip.Color(35, 0, 0));

  setPixel(2, strip.Color(35, 0, 0));
  setPixel(3, strip.Color(35, 0, 0));
  setPixel(4, strip.Color(35, 0, 0));
  setPixel(5, strip.Color(35, 0, 0));

  setPixel(N_LEDS-i-1, strip.Color(35, 0, 0));
  setPixel(N_LEDS-i, strip.Color(35, 0, 0));
  strip.show(); // show this pixel, and any others who's colors have been set lately
  delay(250);

  setPixel(i, strip.Color(0, 35, 0));
  setPixel(i-1, strip.Color(0, 35, 0));
  setPixel(N_LEDS-i-1, strip.Color(0, 35, 0));
  setPixel(N_LEDS-i, strip.Color(0, 35, 0));
  strip.show(); // show this pixel, and any others who's colors have been set lately
  delay(250);

  setPixel(i, strip.Color(0, 0, 35));
  setPixel(i-1, strip.Color(0, 0, 35));
  setPixel(N_LEDS-i-1, strip.Color(0, 0, 35));
  setPixel(N_LEDS-i, strip.Color(0, 0, 35));
  strip.show(); // show this pixel, and any others who's colors have been set lately
  delay(250);

  setPixel(i, strip.Color(0, 0, 0));
  setPixel(i-1, strip.Color(0, 0, 0));

  setPixel(2, strip.Color(0, 0, 0));
  setPixel(3, strip.Color(0, 0, 0));
  setPixel(4, strip.Color(0, 0, 0));
  setPixel(5, strip.Color(0, 0, 0));

  setPixel(N_LEDS-i-1, strip.Color(0, 0, 0));
  setPixel(N_LEDS-i, strip.Color(0, 0, 0));
  strip.show(); // show this pixel, and any others who's colors have been set lately
  delay(650);

  // chase(strip.Color(35, 0, 0)); // Red
  // delay(250);
  // chase(strip.Color(0, 35, 0)); // Green
  // delay(250);
  // chase(strip.Color(0, 0, 35)); // Blue
  // delay(250);
}

static void setPixel(uint16_t i, uint32_t c)
{
  strip.setPixelColor(i, c); // Set the color for one new pixel
  // strip.show(); // show this pixel, and any others who's colors have been set lately
}

static void chase(uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++)
  {
    strip.setPixelColor(i, c);     // Draw new pixel
    strip.setPixelColor(i - 4, 0); // Erase pixel a few steps back
    strip.show();
    delay(63);
  }
}