#include "Arduino.h"
#include "pin_config.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

double offsetX = 0; 
double offsetY = 0; 
double zoom = 1.0;

double cr = -0.7; // Constant real component for Julia set
double ci = 0.27015; // Constant imaginary component for Julia set

void setup() {
  Serial.begin(115200);
  pinMode(TFT_LEDA_PIN, OUTPUT);
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  digitalWrite(TFT_LEDA_PIN, 0);
}

void loop() {
  drawJuliaSet();
  zoom *= 0.95;

  if (zoom < 0.01) {
    zoom = 1.0;
  }
  delay(100);
}

void drawJuliaSet() {
  for(int x = 0; x < 160; x++) {
    for(int y = 0; y < 80; y++) {
      double zx = (x - 80.0) * zoom + offsetX;
      double zy = (y - 40.0) * zoom + offsetY;
      int iter = 0;
      while (zx * zx + zy * zy < 4 && iter < 255) {
        double tempzx = zx * zx - zy * zy + cr;
        zy = 2.0 * zx * zy + ci;
        zx = tempzx;
        iter++;
      }
      if (iter < 255) {
        uint8_t blue = iter % 8 * 32; 
        uint8_t green = iter % 16 * 16; 
        uint8_t red = iter % 32 * 8;
        tft.drawPixel(x, y, tft.color565(red, green, blue));
      } else {
        tft.drawPixel(x, y, TFT_BLACK);
      }
    }
  }
}
