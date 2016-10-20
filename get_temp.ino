//function to read temp and return degrees celcius
void get_temp(){
  int analog_val;
  analog_val = analogRead(2);
  float voltage = analog_val * (5.0 / 1023.0);
  float temp = (voltage - 1.25)/0.005;  
  while(temp < 190){
  Serial.println("Temp too low.. Why dont you go get a coffe and chill while it warms up.");
  delay(5000);
  }
  while(temp > 230){
  Serial.println("Temp too high.. Hold on while I cool off a little.");
  delay(5000);
  }
}
