#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_NeoPixel.h>


//Defines for Pin to box/strip locations

//maybe i'll redefine?



//Defines for NeoPixel Strips
//Don't use pin 10. Doesnt work for whatever reason.
//Expansion board 0 "drains"
Adafruit_NeoPixel rainDrain    = Adafruit_NeoPixel(5, 12, NEO_GRB + NEO_KHZ800);    // Rain to Florida Aquifer pipe on pin 12
Adafruit_NeoPixel surfaceDrain = Adafruit_NeoPixel(5, 11, NEO_GRB + NEO_KHZ800);    // Surface Water to florida aquifer on pin 11
Adafruit_NeoPixel aquiDrain = Adafruit_NeoPixel(5, 9, NEO_GRB + NEO_KHZ800);        // Aquifer Drain on pin 9
//Expansion board 1 "drains"
Adafruit_NeoPixel oceanDrain   = Adafruit_NeoPixel(5, 8, NEO_GRB + NEO_KHZ800);     //
Adafruit_NeoPixel desalDrain   = Adafruit_NeoPixel(5, 7, NEO_GRB + NEO_KHZ800);     // 
Adafruit_NeoPixel recDrain     = Adafruit_NeoPixel(5, 6, NEO_GRB + NEO_KHZ800);     //
//Bottom Drain Level
Adafruit_NeoPixel agroDrain    = Adafruit_NeoPixel(5, 5, NEO_GRB + NEO_KHZ800);     // 
Adafruit_NeoPixel homeDrain    = Adafruit_NeoPixel(5, 4, NEO_GRB + NEO_KHZ800);     // 
Adafruit_NeoPixel indDrain     = Adafruit_NeoPixel(5, 13, NEO_GRB + NEO_KHZ800);    // 


// Define MCP expanders
Adafruit_MCP23017 expBoard0;
Adafruit_MCP23017 expBoard1;
Adafruit_MCP23017 expBoard2;

// set some global vars  
int section = 0;
boolean hold = false;

void setup(){
//Arduino Pin Defines
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
// Initialize all MCP Expanders
  expBoard0.begin(0);
    expBoard0.pinMode(8,  OUTPUT);    // GPB0
    expBoard0.pinMode(9,  OUTPUT);    // GPB1
    expBoard0.pinMode(10, OUTPUT);    // GPB2
    expBoard0.pinMode(11, OUTPUT);    // GPB3
    expBoard0.pinMode(12, OUTPUT);    // GPB4
    expBoard0.pinMode(13, OUTPUT);    // GPB5
    expBoard0.pinMode(14, OUTPUT);    // GPB6
    expBoard0.pinMode(15, OUTPUT);    // GPB7
    expBoard0.pinMode(7,  OUTPUT);    // GPA7
  expBoard1.begin(1);
    expBoard1.pinMode(8,  OUTPUT);    // GPB0
    expBoard1.pinMode(9,  OUTPUT);    // GPB1
    expBoard1.pinMode(10, OUTPUT);    // GPB2
    expBoard1.pinMode(11, OUTPUT);    // GPB3
    expBoard1.pinMode(12, OUTPUT);    // GPB4
    expBoard1.pinMode(13, OUTPUT);    // GPB5
    expBoard1.pinMode(14, OUTPUT);    // GPB6
    expBoard1.pinMode(15, OUTPUT);    // GPB7
    expBoard1.pinMode(7,  OUTPUT);    // GPA7
  expBoard2.begin(2);
    expBoard2.pinMode(8,  OUTPUT);    // GPB0
    expBoard2.pinMode(9,  OUTPUT);    // GPB1
    expBoard2.pinMode(10, OUTPUT);    // GPB2
    expBoard2.pinMode(11, OUTPUT);    // GPB3
    expBoard2.pinMode(12, OUTPUT);    // GPB4
    expBoard2.pinMode(13, OUTPUT);    // GPB5
    expBoard2.pinMode(14, OUTPUT);    // GPB6
    expBoard2.pinMode(15, OUTPUT);    // GPB7
    expBoard2.pinMode(7,  OUTPUT);    // GPA7

//Initialize all the strips
  rainDrain.begin();
  surfaceDrain.begin();
  aquiDrain.begin();
  oceanDrain.begin();
  desalDrain.begin();
  recDrain.begin();
  agroDrain.begin();
  homeDrain.begin();
  indDrain.begin();
//Initialize all pixels to off
  rainDrain.show();
  surfaceDrain.show();
  aquiDrain.show();
  oceanDrain.show();
  desalDrain.show();
  recDrain.show();
  agroDrain.show();
  homeDrain.show();
  indDrain.show();
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
    case 0:
      Serial.println ("Program running - Awaiting remote input");  
      break;
    case 1: 
      fillRainWater (250);          // Call rain water filling state. Number indicates delay time passed into function to fill
      hold = true;
      Serial.println("Rain Water Filled");
      break;
      //
    case 2:
      fillSurfaceWater (250);
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
      fillOceans (250); // Fill rate
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
      drainOUC (0, 0, 255 , 100, 5); // Drain OUC and Animate last pipes - filling final boxes
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
    // Code Below turns on each LED line one at a time, starting from bottom up
    expBoard0.digitalWrite(8, HIGH);
    delay (wait);
    expBoard0.digitalWrite(9, HIGH);
    delay (wait);    
    expBoard0.digitalWrite(10, HIGH);
  }

void fillSurfaceWater (int wait){
    Serial.println("Filling Surface Water");
    // Code Below turns on each LED line one at a time, starting from bottom up
    expBoard0.digitalWrite(11, HIGH);
    delay (wait);
    expBoard0.digitalWrite(12, HIGH);
    delay (wait);    
    expBoard0.digitalWrite(13, HIGH);
  }

void fillOceans (int wait){
    Serial.println("Filling Ocean Water");
    // Code Below turns on each LED line one at a time, starting from bottom up
    expBoard1.digitalWrite(8, HIGH);
    delay (wait);
    expBoard1.digitalWrite(9, HIGH);
    delay (wait);    
    expBoard1.digitalWrite(10, HIGH);
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
 for (int cycle = 0; cycle < 3; cycle++){
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        rainDrain.setPixelColor(i, rainDrain.Color(r,g,b));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, rainDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, rainDrain.Color(r,g,(b-200)));
        rainDrain.setPixelColor(i-3, rainDrain.Color(r,g,(b-250))); 
        rainDrain.setPixelColor(i-4, rainDrain.Color(0,0,0));
        surfaceDrain.setPixelColor(i, surfaceDrain.Color(r,g,b));         //Primary light/pixel
        surfaceDrain.setPixelColor(i-1, surfaceDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        surfaceDrain.setPixelColor(i-2, surfaceDrain.Color(r,g,(b-200)));
        surfaceDrain.setPixelColor(i-3, surfaceDrain.Color(r,g,(b-250))); 
        surfaceDrain.setPixelColor(i-4, surfaceDrain.Color(0,0,0));
        rainDrain.show();
        surfaceDrain.show();

      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        rainDrain.setPixelColor(i, (0));         //Primary light/pixel
        rainDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        rainDrain.setPixelColor(i-2, (0));
        rainDrain.setPixelColor(i-3, (0)); 
        rainDrain.setPixelColor(i-4, (0));
        surfaceDrain.setPixelColor(i, (0));         //Primary light/pixel
        surfaceDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        surfaceDrain.setPixelColor(i-2, (0));
        surfaceDrain.setPixelColor(i-3, (0)); 
        surfaceDrain.setPixelColor(i-4, (0));        
        rainDrain.show();
        surfaceDrain.show();
      delay(wait);
    }
  }
   // Write code here to "fill" the aquifer tank
       Serial.println(cycle);        // Print the cycle var
       expBoard0.digitalWrite(10 - (cycle), LOW);      // Drain rain tanks with each loop
       expBoard0.digitalWrite(13 - (cycle), LOW);      // Drain Surface tank with each loop    
       switch(cycle){                                  // monitor the cycle and turn on the appropraite lights to the aquifer tank. Out of order because of my poor hardware planning...
         case 0:
           expBoard0.digitalWrite(14, HIGH);           // Bottom Row
           Serial.println("case0");
           break;
         case 1:
           expBoard0.digitalWrite(15, HIGH);           //Middle Row
           break;
         case 2:
           expBoard0.digitalWrite(7, HIGH);            //Top Row
           break;
       }
 }
} 
void drainOceans(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining Oceans to Desalinization Plant");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int cycle = 0; cycle < 3; cycle++){
   // Write code here to "fill" the Desal tank and Drain the oceans
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        oceanDrain.setPixelColor(i, oceanDrain.Color(r,g,b));         //Primary light/pixel
        oceanDrain.setPixelColor(i-1, oceanDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        oceanDrain.setPixelColor(i-2, oceanDrain.Color(r,g,(b-200)));
        oceanDrain.setPixelColor(i-3, oceanDrain.Color(r,g,(b-250))); 
        oceanDrain.setPixelColor(i-4, oceanDrain.Color(0,0,0));
        oceanDrain.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        oceanDrain.setPixelColor(i, (0));         //Primary light/pixel
        oceanDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        oceanDrain.setPixelColor(i-2, (0));
        oceanDrain.setPixelColor(i-3, (0)); 
        oceanDrain.setPixelColor(i-4, (0));
        oceanDrain.show();
      delay(wait);
    }
  }
   // Write code here to "fill" the desal tank and drain ocean tank
       Serial.println(cycle);        // Print the cycle var
       expBoard1.digitalWrite(10 - (cycle), LOW);      // Drain ocean tank with each loop
       expBoard1.digitalWrite(11 + (cycle), HIGH);      // Fill Desal tank with each loop    
       
  }
} 


void fillOUC(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining Aquifer and  Desalinization Plant to OUC Treatment");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int cycle = 0; cycle < 3; cycle++){
   // Write code here to "fill" the Desal tank and Drain the oceans
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        aquiDrain.setPixelColor(i, aquiDrain.Color(r,g,b));         //Primary light/pixel
        aquiDrain.setPixelColor(i-1, aquiDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        aquiDrain.setPixelColor(i-2, aquiDrain.Color(r,g,(b-200)));
        aquiDrain.setPixelColor(i-3, aquiDrain.Color(r,g,(b-250))); 
        aquiDrain.setPixelColor(i-4, aquiDrain.Color(0,0,0));
        desalDrain.setPixelColor(i, desalDrain.Color(r,g,b));         //Primary light/pixel
        desalDrain.setPixelColor(i-1, desalDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        desalDrain.setPixelColor(i-2, desalDrain.Color(r,g,(b-200)));
        desalDrain.setPixelColor(i-3, desalDrain.Color(r,g,(b-250))); 
        desalDrain.setPixelColor(i-4, desalDrain.Color(0,0,0));
        desalDrain.show();
        aquiDrain.show();
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        aquiDrain.setPixelColor(i, (0));         //Primary light/pixel
        aquiDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        aquiDrain.setPixelColor(i-2, (0));
        aquiDrain.setPixelColor(i-3, (0)); 
        aquiDrain.setPixelColor(i-4, (0));
        desalDrain.setPixelColor(i, (0));         //Primary light/pixel
        desalDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        desalDrain.setPixelColor(i-2, (0));
        desalDrain.setPixelColor(i-3, (0)); 
        desalDrain.setPixelColor(i-4, (0));
        desalDrain.show();
        aquiDrain.show();
      delay(wait);
    }
  }
       Serial.println(cycle);        // Print the cycle var
       expBoard1.digitalWrite(13 - (cycle), LOW);      // Drain Desal tank with each loop    
       switch(cycle){                                  // monitor the cycle and turn on the appropraite lights to the aquifer tank. Out of order because of my poor hardware planning...
         case 0:
           expBoard0.digitalWrite(7, LOW);             // Top Row of aquifer tank to off
           expBoard1.digitalWrite(14, HIGH);           // Turn on bottom row of OUC Plant
           Serial.println("case0");
           break;
         case 1:
           expBoard0.digitalWrite(15, LOW);           // Middle Row of aquifer tank to off
           expBoard1.digitalWrite(15, HIGH);          // Turn on middle row of OUC Plant
           break;
         case 2:
           expBoard0.digitalWrite(14, LOW);           // Bottom Row of aquifer tank to off
           expBoard1.digitalWrite(17, HIGH);          // Turn on top row of OUC Plant
           break;
       }
   }
} 

void drainOUC(int r, int g, int b, int wait, int nPixels) {
  Serial.println("Draining OUC and animating final pipes. Filling end users");
  int i;                                                              // pixel location, starting with 0  
  int n;                                                              // program cycle number       
  //
 for (int cycle = 0; cycle < 3; cycle++){
   // Write code here to "fill" the Desal tank and Drain the oceans
    for (n = 0; n < 2; n++){                                              
      for(i = 0; i <= nPixels; i++) {                              //Progresses the light down the strip, with a 3 segment trail
        agroDrain.setPixelColor(i, agroDrain.Color(r,g,b));         //Primary light/pixel
        agroDrain.setPixelColor(i-1, agroDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        agroDrain.setPixelColor(i-2, agroDrain.Color(r,g,(b-200)));
        agroDrain.setPixelColor(i-3, agroDrain.Color(r,g,(b-250))); 
        agroDrain.setPixelColor(i-4, agroDrain.Color(0,0,0));
 //     
        homeDrain.setPixelColor(i, homeDrain.Color(r,g,b));         //Primary light/pixel
        homeDrain.setPixelColor(i-1, homeDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        homeDrain.setPixelColor(i-2, homeDrain.Color(r,g,(b-200)));
        homeDrain.setPixelColor(i-3, homeDrain.Color(r,g,(b-250))); 
        homeDrain.setPixelColor(i-4, homeDrain.Color(0,0,0));   
//
        indDrain.setPixelColor(i, indDrain.Color(r,g,b));         //Primary light/pixel
        indDrain.setPixelColor(i-1, indDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        indDrain.setPixelColor(i-2, indDrain.Color(r,g,(b-200)));
        indDrain.setPixelColor(i-3, indDrain.Color(r,g,(b-250))); 
        indDrain.setPixelColor(i-4, indDrain.Color(0,0,0));   
//       
        recDrain.setPixelColor(i, recDrain.Color(r,g,b));         //Primary light/pixel
        recDrain.setPixelColor(i-1, recDrain.Color(r,g,(b-150))); //light fall off below - add more lines to make trail longer 
        recDrain.setPixelColor(i-2, recDrain.Color(r,g,(b-200)));
        recDrain.setPixelColor(i-3, recDrain.Color(r,g,(b-250))); 
        recDrain.setPixelColor(i-4, recDrain.Color(0,0,0));   
//             
        agroDrain.show();
        homeDrain.show();
        indDrain.show();
        recDrain.show();
       
      delay(wait);  
      }
    for(i = 0; i <= nPixels; i++) {     
      //Clear the lights
        agroDrain.setPixelColor(i, (0));         //Primary light/pixel
        agroDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        agroDrain.setPixelColor(i-2, (0));
        agroDrain.setPixelColor(i-3, (0)); 
        agroDrain.setPixelColor(i-4, (0));
//
        homeDrain.setPixelColor(i, (0));         //Primary light/pixel
        homeDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        homeDrain.setPixelColor(i-2, (0));
        homeDrain.setPixelColor(i-3, (0)); 
        homeDrain.setPixelColor(i-4, (0));
//
        indDrain.setPixelColor(i, (0));         //Primary light/pixel
        indDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        indDrain.setPixelColor(i-2, (0));
        indDrain.setPixelColor(i-3, (0)); 
        indDrain.setPixelColor(i-4, (0));
//
        recDrain.setPixelColor(i, (0));         //Primary light/pixel
        recDrain.setPixelColor(i-1, (0)); //light fall off below - add more lines to make trail longer 
        recDrain.setPixelColor(i-2, (0));
        recDrain.setPixelColor(i-3, (0)); 
        recDrain.setPixelColor(i-4, (0));
//
        agroDrain.show();
        homeDrain.show();
        indDrain.show();
        recDrain.show();
      delay(wait);
    }
  }
 }
} 



//EOF
