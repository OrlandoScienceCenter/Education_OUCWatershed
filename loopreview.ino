void loop() {
// Set the remote inputs equal to 0, and check to see if the button has been pressed. 
// If A is pressed, add to the section. If B is pressed, go back
// Also sets / resets the hold variable to prevent show repeats
int btnA = 0;
int btnB = 0;
btnA = digitalRead (A3);
btnB = digitalRead (A4);
if btnA == 1{
  section++;
  hold = 0;
}
if btnB == 1{
  section--;
  hold = 0;
}
  
if (hold == 0){
  switch (section){ 
    case 1: 
      sect1 (0, 0, 255 , 100, 5); // R, G, B, Speed, Strip Length
      hold = 1;
      break;
    case 2:
      sect2 (0, 0, 255 , 100, 5);
      break;
     delay (100);
    }
}
}
