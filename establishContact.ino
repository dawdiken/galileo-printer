//function to sit in while printer gets ready to print. 

void establishContact() {   //for initial identification
    int green_State; // green button
    int man_State; // manual mode swithch 
    // if start has not been pressed. do the following untill it is pressed
    while (start == 0) {
      ether();//build web page
      man_State = digitalRead(7); //read manual mode switch state
      Serial.println("Waiting to print");
      delay(500);
      //while manual mode is on do the following 
      while(man_State == HIGH){ 
        delay(500);
        Manual_mode();
        Serial.println("IN MANUAL MODER");
        Serial.print("stopp = ");//interupt flag
        Serial.println(stopp);
        man_State = digitalRead(7);
        }
    delay(500);
    green_State = digitalRead(3);
    if(green_State == LOW){     
    start = 1;
      }
    } 
   }
