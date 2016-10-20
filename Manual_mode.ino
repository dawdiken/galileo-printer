//function for manual mode button interface

void Manual_mode(){
   int Red_Val = digitalRead(6);
   if(Red_Val == LOW)//clear unwanted alarm alarm
   {
     stopp = 0;
     delay(500);
   }
   int Yellow_Val = digitalRead(4);
  
   //If yellow button pressed home X and Y axis. Auto feature using end stops
   if(Yellow_Val == LOW ){
    home_x_y_axis();
  }
  int Blue_Val =  digitalRead(5);
  // Home Z axis. Manual process as no endstop 
     if (Blue_Val == LOW ){
       AFMS_Z.begin();
     stepperZ->step(5, FORWARD, MICROSTEP);
     Serial.println("Homing Z Axis");
  }
  stepperZ->release();
 }
