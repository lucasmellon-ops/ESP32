#include "Arduino.h"
#include "pin_config.h"
#include "TFT_eSPI.h" // https://github.com/Bodmer/TFT_eSPI

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Serial.println("Mandelbrot Set on T-Dongle-S3");
  pinMode(TFT_LEDA_PIN, OUTPUT);
  
  // Initialise TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  digitalWrite(TFT_LEDA_PIN, 0);
  
  drawMandelbrot();
}

void loop() { // Main loop is empty because Mandelbrot is only drawn once.
}

void drawMandelbrot() {
  for(int x=0; x < 160; x++) {
    for(int y=0; y < 80; y++) {
      double zx = (x - 80.0) / 40.0;  // Adjust these values for zoom and positioning
      double zy = (y - 40.0) / 40.0;  // Adjust these values for zoom and positioning
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
      }
    }
  }
}
