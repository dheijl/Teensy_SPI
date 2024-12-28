#include <Arduino.h>

// https://github.com/vindar/ILI9341_T4
// https://github.com/vindar/ILI9341_T4/blob/main/examples/dualDisplay/dualDisplay.ino
// https://vindar.github.io/tgx/html/md_docs_intro_api_2_d.html#subsec_text

#include <SPI.h>
// the screen driver library
#include <ILI9341_t3n.h>

#undef DEBUG

//
// IL9341 is WIRED TO SPI1
//
const uint8_t PIN_SCK0 = 13;
const uint8_t PIN_MISO0 = 12;
const uint8_t PIN_MOSI0 = 11;
const uint8_t PIN_CS0 = 10;
// if SPI0 is IL9341
const uint8_t PIN_DC0 = 36;         // mandatory, can be any pin but using pin 10 (or 36 or 37 on T4.1) provides greater performance
const uint8_t PIN_RESET0 = 6;       // optional (but recommended), can be any pin.
const uint8_t PIN_BACKLIGHT0 = 255; // optional, set this only if the screen LED pin is connected directly to the Teensy.
const uint8_t PIN_TOUCH_IRQ0 = 255; // optional, set this only if the touchscreen is connected on the same SPI bus
const uint8_t PIN_TOUCH_CS0 = 255;  // optional, set this only if the touchscreen is connected on the same SPI bus

//
// AU IS WIRED TO SPI1
//
const uint8_t PIN_SCK1 = 27;
const uint8_t PIN_MISO1 = 1;  // mandatory  (if the display has no MISO line, set this to 255 but then VSync will be disabled)
const uint8_t PIN_MOSI1 = 26; // mandatory
const uint8_t PIN_DC1 = 38;   // mandatory, can be any pin but using pin 0 (or 38 on T4.1) provides greater performance

const uint8_t PIN_CS1 = 0;          // optional (but recommended), can be any pin.
const uint8_t PIN_RESET1 = 255;     // 29 optional (but recommended), can be any pin.
const uint8_t PIN_BACKLIGHT1 = 255; // optional, set this only if the screen LED pin is connected directly to the Teensy.
const uint8_t PIN_TOUCH_IRQ1 = 255; // optional. set this only if the touchscreen is connected on the same SPI bus
const uint8_t PIN_TOUCH_CS1 = 255;  // optional. set this only if the touchscreen is connected on the same SPI bus

const uint32_t SPI_SPEED = 24000000;

#define LANDSCAPE

const uint8_t ROT_PORTRAIT = 1;
const uint8_t ROT_LANDSCAPE = 0;

#ifdef PORTRAIT
// screen size in portrait mode
const uint32_t LXP = 240;
const uint32_t LYP = 320;
#endif
#ifdef LANDSCAPE
// screen size in landscape mode
const uint32_t LXP = 320;
const uint32_t LYP = 240;
#endif
// screen driver object
static ILI9341_t3n tft(PIN_CS0, PIN_DC0, PIN_RESET0, PIN_MOSI0, PIN_SCK0, PIN_MISO0); // for screen on SPI0

static uint32_t counter = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < 1000; i++)
  {
    delay(1);
    if (Serial.available())
    {
      break;
    }
  }
#ifdef DEBUG
  Serial.println("ILI9341 Test!");
#endif

  // make sure backlight is on
  if (PIN_BACKLIGHT1 != 255)
  {
    pinMode(PIN_BACKLIGHT1, OUTPUT);
    // digitalWrite(PIN_BACKLIGHT1, HIGH);
    analogWrite(PIN_BACKLIGHT1, 128); // PWM backlight level 50 %
  }
  /*
  pinMode(PIN_CS1, OUTPUT);
  SPI.begin();
  SPI1.setCS(PIN_CS1);
  SPI1.setMOSI(PIN_MOSI1);
  SPI1.setMISO(PIN_MISO1);
  SPI1.setSCK(PIN_SCK1);
  SPI1.begin();
  SPI1.beginTransaction(SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE0));
  SPI1.transfer16(0x1234);
  SPI1.endTransaction();
*/
  pinMode(PIN_CS0, OUTPUT);
  tft.begin(); // use default speed (write 30 MHz/ read 2 MHz)
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setRotation(ROT_PORTRAIT);
  tft.setTextSize(1);
  tft.println("tft initialized on SPI 0");
}

void loop()
{
// put your main code here, to run repeatedly:
#ifdef DEBUG
  Serial.println("Tick");
#endif
  tft.print("T");
  ++counter;
  if (counter > 2048)
  {
    tft.setCursor(0, 0);
    tft.fillScreen(ILI9341_BLACK);
    counter = 0;
  }

  delay(1000);
}
