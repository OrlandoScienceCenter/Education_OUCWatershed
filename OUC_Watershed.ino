#include <Adafruit_NeoPixel.h>
#include <Adafruit_MCP23017.h>

//Defines for Pin to box/strip locations
#define RF 
#define SF 10
#define NAD 9

//Defines for NeoPixel Strips
//Top Drain Level
Adafruit_NeoPixel rainDrain = Adafruit_NeoPixel(5, 12, NEO_GRB + NEO_KHZ800);    // Rain to Florida Aquifer pipe on pin 11
Adafruit_NeoPixel surfaceDrain = Adafruit_NeoPixel(5, 11, NEO_GRB + NEO_KHZ800);    // Surface Water to florida aquifer on pin 10
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
rainDrain.begin();
surfaceDrain.begin();
NaDstrip.begin();
//Initialize all pixels to off
rainDrain.show();
surfaceDrain.show();
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
  hold = false;
}
if (btnB == 1){
  section--;
  hold = false;
}
  
if (hold == false){
  switch (section){                 // Fill "Rain Water" box
    case 1: 
      fillRainWater (25);          // Call rain water filling state. Number indicates delay time passed into function to fill
      hold = true;
      Serial.println("Rain Water Filled");
      break;
      //
    case 2:
      fillSurfaceWater (25);
      hold = true;
      Serial.println("Surface Water Filled");
      break;
      //
    case 3:
      drainToAquifer (0, 0, 255 , 100, 5); // R,G,B Color Values, speed value (wait), Pixel StripLength
      hold = true;
      Serial.println("Rain and Surface Tanks Drained");
      break;
      //
    case 4:
      fillOceans (25); // Fill rate
      hold = true;
      Serial.println("Ocean Water Filled");
      break;
      //
    case 5:
      drainOceans (0, 0, 255 , 100, 5); // Drain Oceans to Desalinization Plant, Fill Desal Plant
      hold = true;
      Serial.println("Ocean Water Drained - Desalinization Plant Filled");
      break;
      //
    case 6:
      fillOUC (0, 0, 255 , 100, 5); // Drain Aquifer and Desalinization Plant, Fill OUC Treatment
      hold = true;
      Serial.println("Desalinization and Aquifer Drained - OUC Filled");
      break;
      //
   case 7:
      drainOUC (0, 0, 255 , 100, 5); // Drain OUC and Animate last pipes - not filling final boxes yet
      hold = true;
      Serial.println("OUC Drained, Pipes animated, Lower Boxes Filled");
      break;
      //
   case 8:
      blinkAgro (100);   // Blink and blink rate
      break;                       
      //
   case 9:
      blinkRec(100);   // Blink and blink rate
      break;
      //
   case 10:
      blinkIndustry(100);   // Blink and blink rate
      break;
      //
   case 11:
      blinkHome (100);
      break;
      //
   case 12:
      //Payoff?
      break;
      // 
  default:
      //payoff?
      //party!
     delay (100);
    }
}
}
//END OF LOOP SECTION



/* Random Bits

  sect2 (0, 0, 255 , 100, 5);
*/

void fillRainWater (int wait){
    Serial.println("Filling Rain Water");
    // Write code here to "fill"
    delay (2500);
}

void fillSurfaceWater (int wait){
    Serial.println("Filling Surface Water");
    // Write code here to "fill"
    delay (2500);
}

void fillOceans (int wait){
    Serial.println("Filling Ocean Water");
    // Write code here to "fill"
    delay (2500);
}

void blinkAgro (int wait){};

void blinkRec (int wait){};

void blinkIndustry (int wait){};

void blinkHome (int wait){};




void drainToAquifer(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining Rain and Surface Tanks - Filling Aquifer");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int l = 0; l <= 3; l++){
   // Write code here to "fill" the aquifer tank
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        rainDrain.setPixelColor(i, rainDrain.Color(r,g,b));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, rainDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, rainDrain.Color(r,g,(b-200)));
        rainDrain.setPixelColor(i-3, rainDrain.Color(r,g,(b-250))); 
        rainDrain.setPixelColor(i-4, rainDrain.Color(0,0,0));
        rainDrain.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        rainDrain.setPixelColor(i, (0));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, (0));
        rainDrain.setPixelColor(i-3, (0)); 
        rainDrain.setPixelColor(i-4, (0));
        rainDrain.show();
      delay(wait);
    }
  }
 }
} 
void drainOceans(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining Oceans to Desalinization Plant");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int l = 0; l <= 3; l++){
   // Write code here to "fill" the Desal tank and Drain the oceans
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        rainDrain.setPixelColor(i, rainDrain.Color(r,g,b));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, rainDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, rainDrain.Color(r,g,(b-200)));
        rainDrain.setPixelColor(i-3, rainDrain.Color(r,g,(b-250))); 
        rainDrain.setPixelColor(i-4, rainDrain.Color(0,0,0));
        rainDrain.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        rainDrain.setPixelColor(i, (0));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, (0));
        rainDrain.setPixelColor(i-3, (0)); 
        rainDrain.setPixelColor(i-4, (0));
        rainDrain.show();
      delay(wait);
    }
  }
 }
} 


void fillOUC(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining Aquifer and  Desalinization Plant to OUC Treatment");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int l = 0; l <= 3; l++){
   // Write code here to "fill" the Desal tank and Drain the oceans
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        rainDrain.setPixelColor(i, rainDrain.Color(r,g,b));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, rainDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, rainDrain.Color(r,g,(b-200)));
        rainDrain.setPixelColor(i-3, rainDrain.Color(r,g,(b-250))); 
        rainDrain.setPixelColor(i-4, rainDrain.Color(0,0,0));
        rainDrain.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        rainDrain.setPixelColor(i, (0));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, (0));
        rainDrain.setPixelColor(i-3, (0)); 
        rainDrain.setPixelColor(i-4, (0));
        rainDrain.show();
      delay(wait);
    }
  }
 }
} 

void drainOUC(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining OUC and animating final pipes. Filling end users");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int l = 0; l <= 3; l++){
   // Write code here to "fill" the Desal tank and Drain the oceans
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        rainDrain.setPixelColor(i, rainDrain.Color(r,g,b));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, rainDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, rainDrain.Color(r,g,(b-200)));
        rainDrain.setPixelColor(i-3, rainDrain.Color(r,g,(b-250))); 
        rainDrain.setPixelColor(i-4, rainDrain.Color(0,0,0));
        rainDrain.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        rainDrain.setPixelColor(i, (0));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, (0));
        rainDrain.setPixelColor(i-3, (0)); 
        rainDrain.setPixelColor(i-4, (0));
        rainDrain.show();
      delay(wait);
    }
  }
 }
} 



//EOF
