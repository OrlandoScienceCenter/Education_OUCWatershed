#include <Adafruit_NeoPixel.h>
#include <Wire.h>

//Defines for Pin to box/strip locations
#define RF 11
#define SF 10
#define NAD 9

//Defines for NeoPixel Strips
Adafruit_NeoPixel RFstrip = Adafruit_NeoPixel(5, RF, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SFstrip = Adafruit_NeoPixel(5, SF, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, NAD, NEO_GRB + NEO_KHZ800);


void setup(){
//Initialize all the strips
RFstrip.begin();
SFstrip.begin();
NaDstrip.begin();
//Initialize all pixels to off
RFstrip.show();
SFstrip.show();
NaDstrip.show();
}

void loop() {
   Drain1 (0, 0, 255, 100, 5); // the 4th number controls the speed
  /* RFstrip.setPixelColor(1,RFstrip.Color(255,0,0));
   RFstrip.setPixelColor(2,RFstrip.Color(0,255,0));
   RFstrip.setPixelColor(3,RFstrip.Color(0,0,255));
   //m
   RFstrip.show();
   */
   
}
void Drain1(int r, int g, int b, int wait, int tPixels) {
  for(int i=0; i<tPixels; i++) {
      RFstrip.setPixelColor(i, RFstrip.Color(r,g,b));
      RFstrip.setPixelColor(i-1, RFstrip.Color(r,g,(b-150)));
      RFstrip.setPixelColor(i-2, RFstrip.Color(r,g,(b-200)));
      RFstrip.setPixelColor(i-3, RFstrip.Color(r,g,(b-250))); // add more of these lines to make the trail longer
      RFstrip.show();
      delay(wait);  
  }
  for(int j=0; j<tPixels; j++) {
      RFstrip.setPixelColor(j, RFstrip.Color(0,0,0));
      RFstrip.setPixelColor(j-1, RFstrip.Color(0,0,0));
      RFstrip.setPixelColor(j-2, RFstrip.Color(0,0,0));
      RFstrip.setPixelColor(j-3, RFstrip.Color(0,0,0)); // add more of these lines to make the trail longer
      RFstrip.show();
      delay(wait);  
  }
}

