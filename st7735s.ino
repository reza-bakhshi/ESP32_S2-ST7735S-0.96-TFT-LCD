#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

uint16_t colors[12];

// -------------------------------------------------------------------------
// Setup
// -------------------------------------------------------------------------
void setup(void)
{
  tft.init();
  tft.fillScreen(TFT_BLACK);

  pinMode(TFT_BL, OUTPUT);
  // controll lcd backlight
  for (uint8_t c = 0; c < 3; c++)
  {
    digitalWrite(TFT_BL, LOW);
    delay(1000);
    digitalWrite(TFT_BL, HIGH);
    delay(1000);
  }
  // Create the outer ring colours
  for (uint8_t c = 0; c < 2; c++)
  {
    colors[c + 10] = tft.alphaBlend(128 + c * 127, TFT_RED, TFT_MAGENTA);
    colors[c + 8] = tft.alphaBlend(128 + c * 127, TFT_MAGENTA, TFT_BLUE);
    colors[c + 6] = tft.alphaBlend(128 + c * 127, TFT_BLUE, TFT_GREEN);
    colors[c + 4] = tft.alphaBlend(128 + c * 127, TFT_GREEN, TFT_YELLOW);
    colors[c + 2] = tft.alphaBlend(128 + c * 127, TFT_YELLOW, TFT_ORANGE);
    colors[c + 0] = tft.alphaBlend(128 + c * 127, TFT_ORANGE, TFT_RED);
  }
}

// -------------------------------------------------------------------------
// Main loop
// -------------------------------------------------------------------------
void loop()
{
  uint16_t rDelta = (tft.width() - 1) / 10;
  uint16_t x = tft.width() / 2;
  uint16_t y = tft.height() / 2;
  bool smooth = true;

  // Draw rings as a series of arcs, increasingly blend colour with white towards middle
  for (uint16_t i = 5; i > 0; i--)
  {
    for (uint16_t angle = 0; angle <= 330; angle += 30)
    {
      uint16_t radius = i * rDelta;
      uint16_t wheelColor = tft.alphaBlend((i * 255.0) / 5.0, colors[angle / 30], TFT_WHITE);
      tft.drawArc(x, y, radius, radius - rDelta, angle, angle + 30, wheelColor, TFT_BLACK, smooth);
    }
    smooth = false; // Only outer ring is smooth
  }

  while (1)
    delay(100);
}
