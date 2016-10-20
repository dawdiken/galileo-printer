//interupt function
void extIntISR() 
{
  stopp =! stopp; // goes one when trips then clears its self when moved back off endstop
  // Toggle the on board LED
  long fin = millis();
  if(fin - lastButtonPush > 500)
  { 
    Serial.println("I got an external interrupt!");
    Serial.println("All motors released;");
  } 
  lastButtonPush = fin;
} 
