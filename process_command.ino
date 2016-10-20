/*While data is availible from file (fp) read it line by line. save to string
  break string up to find X Y Z E parts,
  find numerical values after X Y Z E 
  Send to move function
*/
void process_command(){
while(fp)
  {
   inputChar=fgetc(fp); // Gets one byte from serial buffer

    if (inputChar != 10) // Write to string until "end of line" ascii recieved
    {
      inputCharString[stringIndex] = inputChar; // Store it
      stringIndex++; // Increment where to write next
    }
    else  
    {
      inputCharString[stringIndex] = 0; // Add last char as ascii "void" to stop from reading the rest of the string (from prev lines longer than current one)
      String inputString = inputCharString; 
      
      //******processing of Gcode here*****
      if (inputString[0] == 'G' && inputString[1] == '1') // if line starts with a G process it, if not discard it
      {
        int Xpos = inputString.indexOf('X'); //locate the position of X and save its location
        int Ypos = inputString.indexOf('Y'); //locate the position of Y and save its location
        int Epos = inputString.indexOf('E'); //locate the position of E and save its location

        if (Xpos > 0) { 
          stringX = inputString.substring(Xpos+1,Ypos-1) ; // value for X is located between X and Y. If it exists, cut it into a substring
        } // if it doesnt exist it will remain as previous
        if (Ypos > 0) { 
          stringY = inputString.substring(Ypos+1,Epos-1) ; // value for Y is located between Y and Z. If it exists, cut it into a substring
        } // if it doesnt exist it will remain as previous
        if (Epos > 0) { 
          stringE = inputString.substring(Epos+1,Epos+10) ; // value for E is located after the E. no more than 10 chars needed. If it exists, cut it into a substring
        } // if it doesnt exist it will remain as previous

        // TRANSFER X STRING INTO FLOAT (2dec place)
        char carrayX[stringX.length() + 1]; //determine size of the array
        stringX.toCharArray(carrayX, sizeof(carrayX)); //put readStringinto an array
        double  x = atof(carrayX); //convert the array into an Integer 
        
        // TRANSFER Y STRING INTO FLOAT (2dec place)
        char carrayY[stringY.length() + 1]; //determine size of the array
        stringY.toCharArray(carrayY, sizeof(carrayY)); //put readStringinto an array
        double y = atof(carrayY); //convert the array into an Integer 
        
         // TRANSFER E STRING INTO FLOAT (2dec place)
        char carrayE[stringE.length() + 1]; //determine size of the array
        stringE.toCharArray(carrayE, sizeof(carrayE)); //put readStringinto an array
        double e = atof(carrayE); //convert the array into an Integer 

        Serial.print("X: ");
        Serial.print(x);
        Serial.print(" Y: ");
        Serial.print(y);
        Serial.print(" E: ");
        Serial.println(e);
        double xp = x; 
        double yp = y; 
        double ep = e; 
        ether();
        Move(xp,yp,ep);
        
      }
        else if (inputString[0] == 'G' && inputString[1] == '9') // if line starts with a G process it, if not discard it
      {
        Epos = 0;
        Serial.print("Epos:  ");
        Serial.println(Epos);
      }
      else if (inputString[0] == 'M' && inputString[1] == '8' && inputString[2] == '4') // turn off motors
      {
        stepperZ->release();
        stepperX->release();
        stepperY->release();
        stepperE->release();
      }
      else if (inputString[0] == 'G' && inputString[1] == '7') // CENTRE EXTRUDER ON BED
      {
       stepperX->step(350, FORWARD, MICROSTEP);// 
       stepperY->step(350, FORWARD, MICROSTEP);// 
      }
      else if (inputString[0] == 'G' && inputString[1] == '6') // Step Z axis away
      {
       AFMS_Z.begin();
       stepperZ->step(25, BACKWARD, MICROSTEP);  
       stepperZ->release();    
      }
      else if (inputString[0] == 'G' && inputString[1] == '5') // Step Z axis down
      {
       AFMS_Z.begin();
       stepperZ->step(25, FORWARD, MICROSTEP);  
       stepperZ->release();    
      }
      else if (inputString[0] == 'M' && inputString[1] == '2' && inputString[2] == '0') // Home all axis
      {
       home_x_y_axis();    
      }
      else if (inputString[0] == 'M' && inputString[1] == '2' && inputString[2] == '9') // Check extruder temp
      {
        get_temp();
      }
      stringIndex = 0; // clear the String index value for the next cycle
      
    }
    
  }
  }
