#include <Arduino.h>

// https://github.com/vindar/ILI9341_T4
// https://vindar.github.io/tgx/html/md_docs_intro_api_2_d.html#subsec_text

#include <SPI.h>
#include <ILI9341_T4.h>
#include "font_tgx_Arial.h"
#include "font_tgx_OpenSans.h"

static tgx::RGB32 buffer[320 * 240];                //
static tgx::Image<tgx::RGB32> im(buffer, 320, 240); // create a black 320x240 image.

void setup()
{
  // put your setup code here, to run once:
  im.clear(tgx::RGB32_Black);

  // drawing text: the anchor point use the baseline.
  im.drawText("non-AA font are ugly...", {5, 10}, font_tgx_Arial_8, tgx::RGB32_Blue); // a non AA font
  im.drawText("AA font, 9pt", {5, 25}, font_tgx_OpenSans_9, tgx::RGB32_Green);        // AA font, 9pt
  im.drawText("AA font, 10pt", {5, 40}, font_tgx_OpenSans_10, tgx::RGB32_Green);      // AA font, 10pt
  im.drawText("AA font, 14pt", {5, 60}, font_tgx_OpenSans_14, tgx::RGB32_Green);      // AA font, 14pt
  im.drawText("AA font, 18pt", {5, 83}, font_tgx_OpenSans_20, tgx::RGB32_Green);      // AA font, 18pt

  // drawing on the baseline
  im.drawFastHLine({130, 30}, 160, tgx::RGB32_White, 0.5f);
  im.drawFastHLine({130, 45}, 160, tgx::RGB32_White, 0.5f);
  im.drawText("The quick brown fox jumps", {130, 30}, font_tgx_OpenSans_12, tgx::RGB32_Orange);
  im.drawText("over the lazy dog !", {130, 45}, font_tgx_OpenSans_12, tgx::RGB32_Orange);

  // finding the bounding box of a text.
  const char *tbb = "Text bounding box";
  tgx::iBox2 bb = im.measureText(tbb, {230, 70}, font_tgx_OpenSans_14, tgx::Anchor::CENTER, false, false);
  im.fillRect(bb, tgx::RGB32_Yellow, 0.5f);
  im.drawTextEx(tbb, {230, 70}, font_tgx_OpenSans_14, tgx::Anchor::CENTER, false, false, tgx::RGB32_Blue);

  // draw text with different anchor points using drawTextEx()
  // -> the anchor is relative to the text bounding box
  im.drawRect({20, 300, 100, 230}, tgx::RGB32_Gray);
  im.drawFastHLine({20, 165}, 280, tgx::RGB32_Gray);
  im.drawFastVLine({160, 100}, 130, tgx::RGB32_Gray);
  tgx::iVec2 anchor_point;

  anchor_point = {20, 100};
  im.drawTextEx("TOPLEFT", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::TOPLEFT, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {300, 100};
  im.drawTextEx("TOPRIGHT", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::TOPRIGHT, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {20, 230};
  im.drawTextEx("BOTTOMLEFT", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::BOTTOMLEFT, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {300, 230};
  im.drawTextEx("BOTTOMRIGHT", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::BOTTOMRIGHT, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {160, 100};
  im.drawTextEx("CENTERTOP", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::CENTERTOP, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {160, 230};
  im.drawTextEx("CENTERBOTTOM", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::CENTERBOTTOM, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {20, 165};
  im.drawTextEx("CENTERLEFT", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::CENTERLEFT, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {300, 165};
  im.drawTextEx("CENTERRIGHT", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::CENTERRIGHT, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);

  anchor_point = {160, 165};
  im.drawTextEx("CENTER", anchor_point, font_tgx_OpenSans_10, tgx::Anchor::CENTER, true, true, tgx::RGB32_Red);
  im.fillCircleAA(anchor_point, 1.5, tgx::RGB32_Green);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
