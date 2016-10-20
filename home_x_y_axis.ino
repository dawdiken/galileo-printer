// Function to home X and Y axis automatically polling the endstop flag
void home_x_y_axis() 
{
  //Home Y axis
  while(stopp == 0){
    Serial.println("Microstep steps");
  stepperX->step(1, BACKWARD, MICROSTEP); //HOME Y AXIS
  }
  stepperX->step(10, FORWARD, MICROSTEP);// move off end stop home
  stopp = 0;
  // Home X Axis
  while(stopp == 0){
    Serial.println("Microstep steps");
  stepperY->step(1, BACKWARD, MICROSTEP); //HOME X AXIS
  }
  stepperY->step(15, FORWARD, MICROSTEP);
  stopp = 0;
  stepperY->release(); //Turn off to save power on idle
  stepperX->release(); //Turn off to save power on idle
  Xpos = 0;
  Ypos = 0;
}
