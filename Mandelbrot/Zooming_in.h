#include "Arduino.h"
#include "pin_config.h"
#include "TFT_eSPI.h" // https://github.com/Bodmer/TFT_eSPI

TFT_eSPI tft = TFT_eSPI();

// Mandelbrot settings
double offsetX = 0; // X offset
double offsetY = 0; // Y offset
double zoom = 1.0; // Zoom level

void setup() {
  Serial.begin(115200);
  pinMode(TFT_LEDA_PIN, OUTPUT);
  
  // Initialise TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  digitalWrite(TFT_LEDA_PIN, 0);
}

void loop() {
  drawMandelbrot();
  zoom *= 0.95; // Zoom in by 5% each frame. You can adjust this rate.

  if (zoom < 0.01) { // Reset zoom after it gets too small.
    zoom = 1.0;
  }
  delay(100); // Delay to control the speed of zoom.
}

void drawMandelbrot() {
  for(int x = 0; x < 160; x++) {
    for(int y = 0; y < 80; y++) {
      double zx = (x - 80.0) * zoom + offsetX;
      double zy = (y - 40.0) * zoom + offsetY;
      double cx = zx;
      double cy = zy;
      int iter = 0;
      double tempzx;
      while(zx * zx + zy * zy < 4 && iter < 255) {
        tempzx = zx * zx - zy * zy + cx;
        zy = 2.0 * zx * zy + cy;
        zx = tempzx;
        iter++;
      }
      if(iter < 255) {
        tft.drawPixel(x, y, tft.color565(iter, iter, iter));
      } else {
        tft.drawPixel(x, y, TFT_BLACK);
      }
    }
  }
}
