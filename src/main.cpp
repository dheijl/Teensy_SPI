#include <Arduino.h>

// https://github.com/vindar/ILI9341_T4
// https://github.com/vindar/ILI9341_T4/blob/main/examples/dualDisplay/dualDisplay.ino
// https://vindar.github.io/tgx/html/md_docs_intro_api_2_d.html#subsec_text

#include <SPI.h>
// the screen driver library
#include <ILI9341_t3.h>

//
// AU IS WIRED TO SPI0
//
#define PIN_SCK0 13
#define PIN_MISO0 12
#define PIN_MOSI0 11
#define PIN_CS0 9
/* if SPI0 is IL9341
#define PIN_DC0 36   // mandatory, can be any pin but using pin 10 (or 36 or 37 on T4.1) provides greater performance
#define PIN_RESET0 6       // optional (but recommended), can be any pin.
#define PIN_BACKLIGHT0 255 // optional, set this only if the screen LED pin is connected directly to the Teensy.
#define PIN_TOUCH_IRQ0 255 // optional, set this only if the touchscreen is connected on the same SPI bus
#define PIN_TOUCH_CS0 255  // optional, set this only if the touchscreen is connected on the same SPI bus
*/
//
// IL9341 is WIRED TO SPI1
//
const uint8_t PIN_SCK1 = 27;
const uint8_t PIN_MISO1 = 1;  // mandatory  (if the display has no MISO line, set this to 255 but then VSync will be disabled)
const uint8_t PIN_MOSI1 = 26; // mandatory
const uint8_t PIN_DC1 = 38;   // mandatory, can be any pin but using pin 0 (or 38 on T4.1) provides greater performance

const uint8_t PIN_CS1 = 30;         // optional (but recommended), can be any pin.
const uint8_t PIN_RESET1 = 29;      // optional (but recommended), can be any pin.
const uint8_t PIN_BACKLIGHT1 = 2;   // optional, set this only if the screen LED pin is connected directly to the Teensy.
const uint8_t PIN_TOUCH_IRQ1 = 255; // optional. set this only if the touchscreen is connected on the same SPI bus
const uint8_t PIN_TOUCH_CS1 = 255;  // optional. set this only if the touchscreen is connected on the same SPI bus

const unsigned long SPI_SPEED = 24000000;

// screen size in portrait mode
#define LPORTRAIT 1
#define LXP 240
#define LYP 320
// screen size in landscape mode
#define LLANDSCAPE 0
#define LXP 320
#define LYP 240
// screen driver object
ILI9341_t3 tft(PIN_CS1, PIN_DC1, PIN_RESET1, PIN_MOSI1, PIN_SCK1, PIN_MISO1); // for screen on SPI1

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial)
    ; // wait for Arduino Serial Monitor
  Serial.println("ILI9341 Test!");

  // make sure backlight is on
  if (PIN_BACKLIGHT1 != 255)
  {
    pinMode(PIN_BACKLIGHT1, OUTPUT);
    // digitalWrite(PIN_BACKLIGHT1, HIGH);
    analogWrite(PIN_BACKLIGHT1, 128); // PWM backlight level 50 %
  }
  tft.setClock(SPI_SPEED);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setRotation(LPORTRAIT);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");

  tft.println();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
