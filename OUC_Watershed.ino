#include <Adafruit_NeoPixel.h>
#include <Wire.h>

//Defines for Pin to box/strip locations
#define RF 
#define SF 10
#define NAD 9

//Defines for NeoPixel Strips
//Top Drain Level
Adafruit_NeoPixel RFstrip = Adafruit_NeoPixel(5, 12, NEO_GRB + NEO_KHZ800);    // Rain to Florida Aquifer pipe on pin 11
Adafruit_NeoPixel SFstrip = Adafruit_NeoPixel(5, 11, NEO_GRB + NEO_KHZ800);    // Surface Water to florida aquifer on pin 10
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 9, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
/*Middle Drain Level
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 8, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 7, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
//Bottom Drain Level
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 6, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 5, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 4, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
Adafruit_NeoPixel NaDstrip = Adafruit_NeoPixel(5, 3, NEO_GRB + NEO_KHZ800);    // Salt Water to Desalinization plant on pin 9
*/
int section = 0;
boolean hold = 1;

void setup(){
Serial.begin(9600);

pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
  
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
// Set the remote inputs equal to 0, and check to see if the button has been pressed. 
// If A is pressed, add to the section. If B is pressed, go back
// Also sets / resets the hold variable to prevent show repeats
boolean btnA = 0;
boolean btnB = 0;
btnA = digitalRead (A3);
btnB = digitalRead (A4);
if (btnA == 1){
  section++;
  hold = 0;
}
if (btnB == 1){
  section--;
  hold = 0;
}
  
if (hold == 0){
  switch (section){ 
    case 1: 
      sect1 (0, 0, 255 , 100, 5); // R, G, B, Speed, Strip Length
      hold = !hold;
      Serial.println("Section 1 Returned");
      break;
    case 2:
      sect2 (0, 0, 255 , 100, 5);
      hold = !hold;
      Serial.println("Section 2 Returned");
      break;
    default:
      
      //party!
     delay (100);
    }
}
}





void sect1(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Section 1 Active");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int l = 0; l <= 3; l++){
    for (n = 0; n < 6; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        RFstrip.setPixelColor(i, RFstrip.Color(r,g,b));         //Primary light/pixel
        RFstrip.setPixelColor(i-1, RFstrip.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        RFstrip.setPixelColor(i-2, RFstrip.Color(r,g,(b-200)));
        RFstrip.setPixelColor(i-3, RFstrip.Color(r,g,(b-250))); 
        RFstrip.setPixelColor(i-4, RFstrip.Color(0,0,0));
        RFstrip.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        RFstrip.setPixelColor(i, (0));         //Primary light/pixel
        RFstrip.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        RFstrip.setPixelColor(i-2, (0));
        RFstrip.setPixelColor(i-3, (0)); 
        RFstrip.setPixelColor(i-4, (0));
        RFstrip.show();
      delay(wait);
    }
  }
 }
} //END OF LOOP SECTION


void sect2(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Section 2 Active");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
  for (int l = 0; l <= 3; l++){
    for (n = 0; n < 6; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        SFstrip.setPixelColor(i, SFstrip.Color(r,g,b));         //Primary light/pixel
        SFstrip.setPixelColor(i-1, SFstrip.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        SFstrip.setPixelColor(i-2, SFstrip.Color(r,g,(b-200)));
        SFstrip.setPixelColor(i-3, SFstrip.Color(r,g,(b-250))); 
        SFstrip.setPixelColor(i-4, SFstrip.Color(0,0,0));
        SFstrip.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        SFstrip.setPixelColor(i, (0));         //Primary light/pixel
        SFstrip.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        SFstrip.setPixelColor(i-2, (0));
        SFstrip.setPixelColor(i-3, (0)); 
        SFstrip.setPixelColor(i-4, (0));
        SFstrip.show();
      delay(wait);
      }
    } 
  }


}

//EOF
