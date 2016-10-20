//use BRESHENHAM’S ALGORITHM to move machine from current position to next position

void Move ( signed long int newX, signed long int newY,signed long int newE) {
  float distance = 0;
  int stepnum = 0;
  signed long int nextX;
  signed long int nextY;
  signed long int nextE;
  signed long int oldX = Xpos;
  signed long int oldY = Ypos;
  signed long int oldE = Epos;
  ether();
  //find the hypotenuse, the total distance to be traveled
  distance = sqrt((newX - oldX)*(newX - oldX) + (newY - oldY)*(newY - oldY) ) + 0.5;

  //round to integer number of steps that distance. Step by two to minimize 0 size steps.
  for (stepnum=0; stepnum <= distance; stepnum++) {
  
    //calculate the nearest integer points along the way 
    nextX = oldX + stepnum/distance*(newX-oldX);
    nextY = oldY + stepnum/distance*(newY-oldY);
   // nextE = oldE + stepnum/distance*(newE-oldE);

    //move machine to that new coordinate, if 0 delta, don't move
    if ((distance < 4*INCH) && (distance > -4*INCH)) { //trap crazy values
      if ((nextX-Xpos) >=  1)  stepperX->step((nextX - Xpos), FORWARD, MICROSTEP); 
      if ((nextX-Xpos) <= -1)  stepperX->step((Xpos - nextX), BACKWARD, MICROSTEP);
      if ((nextY-Ypos) >=  1)  stepperY->step((nextY - Ypos), FORWARD, MICROSTEP); 
      if ((nextY-Ypos) <= -1)  stepperY->step((Ypos - nextY), BACKWARD, MICROSTEP);
      //if ((nextE-Epos) >=  1)  stepperE->step((nextE - Epos), FORWARD, MICROSTEP); 
      //if ((nextE-Epos) <= -1)  stepperE->step((Epos - nextE), BACKWARD, MICROSTEP);
      ether();
      while(stopp==1){
      stepperX->release();
      stepperY->release();
      stepperZ->release();
      stepperE->release();
      Serial.println("endstop");
      ether();
      }
    //update the machine current position
    Xpos = nextX;
    Ypos = nextY;
    Epos = nextE;
    } else {
      Serial.println("ERROR! Distance too big");
      break;
    }
  }
  
  // correct for rounding down errors
  if ((abs(newX-Xpos)<6) && (abs(newY-Ypos)<6)) { //IGNORE LARGE values
      if ((newX-Xpos) >  0)  stepperX->step((newX - Xpos), FORWARD, MICROSTEP); 
      if ((newX-Xpos) < 0)  stepperX->step((Xpos - newX), BACKWARD, MICROSTEP);
      if ((newY-Ypos) >  0)  stepperY->step((newY - Ypos), FORWARD, MICROSTEP); 
      if ((newY-Ypos) < 0)  stepperY->step((Ypos - newY), BACKWARD, MICROSTEP);
      //if ((newE-Epos) >  0)  stepperE->step((newE - Epos), FORWARD, MICROSTEP); 
      //if ((newE-Epos) < 0)  stepperE->step((Epos - newE), BACKWARD, MICROSTEP);
  }
    //update the machine current position
    Xpos = newX;
    Ypos = newY;
    Epos = newE;
}
