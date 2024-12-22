#include <Arduino.h>

// https://github.com/vindar/ILI9341_T4
// https://github.com/vindar/ILI9341_T4/blob/main/examples/dualDisplay/dualDisplay.ino
// https://vindar.github.io/tgx/html/md_docs_intro_api_2_d.html#subsec_text

#include <SPI.h>
#include <ILI9341_T4.h>

// the screen driver library
#include <ILI9341_T4.h>

//
// FIRST SCREEN IS WIRED TO SPI0
//
/*
#define PIN_SCK0 13  // mandatory
#define PIN_MISO0 12 // mandatory  (if the display has no MISO line, set this to 255 but then VSync will be disabled)
#define PIN_MOSI0 11 // mandatory
#define PIN_DC0 10   // mandatory, can be any pin but using pin 10 (or 36 or 37 on T4.1) provides greater performance

#define PIN_CS0 9          // optional (but recommended), can be any pin.
#define PIN_RESET0 6       // optional (but recommended), can be any pin.
#define PIN_BACKLIGHT0 255 // optional, set this only if the screen LED pin is connected directly to the Teensy.
#define PIN_TOUCH_IRQ0 255 // optional, set this only if the touchscreen is connected on the same SPI bus
#define PIN_TOUCH_CS0 255  // optional, set this only if the touchscreen is connected on the same SPI bus
*/
//
// SECOND SCREEN IS WIRED TO SPI1
//
#define PIN_SCK1 27  // mandatory
#define PIN_MISO1 1  // mandatory  (if the display has no MISO line, set this to 255 but then VSync will be disabled)
#define PIN_MOSI1 26 // mandatory
#define PIN_DC1 0    // mandatory, can be any pin but using pin 0 (or 38 on T4.1) provides greater performance

#define PIN_CS1 30         // optional (but recommended), can be any pin.
#define PIN_RESET1 29      // optional (but recommended), can be any pin.
#define PIN_BACKLIGHT1 255 // optional, set this only if the screen LED pin is connected directly to the Teensy.
#define PIN_TOUCH_IRQ1 255 // optional. set this only if the touchscreen is connected on the same SPI bus
#define PIN_TOUCH_CS1 255  // optional. set this only if the touchscreen is connected on the same SPI bus

#define SPI_SPEED 240000000

// screen size in portrait mode
#define LX 240
#define LY 320

// screen driver objects
// ILI9341_T4::ILI9341Driver tft0(PIN_CS0, PIN_DC0, PIN_SCK0, PIN_MOSI0, PIN_MISO0, PIN_RESET0, PIN_TOUCH_CS0, PIN_TOUCH_IRQ0); // for screen on SPI0
ILI9341_T4::ILI9341Driver tft1(PIN_CS1, PIN_DC1, PIN_SCK1, PIN_MOSI1, PIN_MISO1, PIN_RESET1, PIN_TOUCH_CS1, PIN_TOUCH_IRQ1); // for screen on SPI1

// framebuffers
//  uint16_t internal_fb0[LX * LY]; // internal fb used by the library for the first screen
DMAMEM uint16_t internal_fb1[LX * LY]; // internal fb used by the library for the second screen
uint16_t fb[LX * LY];                  // main framebuffer we draw onto

// 4 diff buffers with about 6K memory each
/*
ILI9341_T4::DiffBuffStatic<6000> diff1; // for the driver on SPI0
ILI9341_T4::DiffBuffStatic<6000> diff2; //
*/
ILI9341_T4::DiffBuffStatic<6000> diff3; // for the driver on SPI1
ILI9341_T4::DiffBuffStatic<6000> diff4; //

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // use USB serial for debug information / troubleshooting.
  // tft0.output(&Serial);
  tft1.output(&Serial);

  // init the screens
  /*
  while (!tft0.begin(SPI_SPEED))
  {
    Serial.print("\n\n\n ****** ERROR CONNECTING TO ILI9341 SCREEN ON SPI 0 ****** \n\n");
    delay(1000);
  }
  */
  while (!tft1.begin(SPI_SPEED))
  {
    Serial.print("\n\n\n ****** ERROR CONNECTING TO ILI9341 SCREEN ON SPI 1 ****** \n\n");
    delay(1000);
  }
  /*
    // set parameters for the first display
    tft0.setRotation(0);                 // portrait mode 240 x320
    tft0.setFramebuffer(internal_fb0);   // set the internal framebuffer (enables double buffering)
    tft0.setDiffBuffers(&diff1, &diff2); // set the 2 diff buffers => activate differential updates.
    tft0.setDiffGap(4);                  // use a small gap for the diff buffers
    tft0.setRefreshRate(150);            // max refresh rate.
    tft0.setVSyncSpacing(2);             // set framerate = refreshrate/2 (and enable vsync at the same time).
  */
  // set parameters for the second display
  tft1.setRotation(0);                 // portrait mode 240 x320
  tft1.setFramebuffer(internal_fb1);   // set the internal framebuffer (enables double buffering)
  tft1.setDiffBuffers(&diff3, &diff4); // set the 2 diff buffers => activate differential updates.
  tft1.setDiffGap(4);                  // use a small gap for the diff buffers
  tft1.setRefreshRate(120);            // max refresh rate.
  tft1.setVSyncSpacing(2);             // set framerate = refreshrate/2 (and enable vsync at the same time).

  // make sure backlight is on
  /*
  if (PIN_BACKLIGHT0 != 255)
  {
    pinMode(PIN_BACKLIGHT0, OUTPUT);
    digitalWrite(PIN_BACKLIGHT0, HIGH);
  }
  */
  if (PIN_BACKLIGHT1 != 255)
  {
    pinMode(PIN_BACKLIGHT1, OUTPUT);
    digitalWrite(PIN_BACKLIGHT1, HIGH);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}
