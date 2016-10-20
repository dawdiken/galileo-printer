/*
 Author:        David kenny Group C year, 3, Computer and Electronic Engineering. 
 Program:       Intel Galileo 3D printer
 Description:   Interpret G-Code comands and execute movements accordingly.
                Respond to manual input form user interface.
                Host web server on Intel galileo and display information about printer status on a web page.
                Respond to alram inputs.       
 Sources: Code used inclde; arduino example codes. GRBL cnc tutorials. Adafruit mototr shield         
 */
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#define INCH 140
FILE *fp;

char inputCharString [100]; // reserve room for intput string. 
char inputChar; //varible to store new characters into
int stringIndex = 0; // String stringIndexing int;

//string variables for X, Y, Z, E varibles
String stringX; 
String stringY;
String stringE;
String stringZ;

//set axis location to zero on start
signed long int Xpos = 0;
signed long int Ypos = 0;
signed long int Zpos = 0;
signed long int Epos = 0;

// Set up the destination machine position variables
signed long int newXpos = 0;
signed long int newYpos = 0;
signed long int newZpos = 0;

double x = 0;
double y = 0;
double e = 0;
int i = 0;
int inByte = 0;
float X_axis = 0;
float Y_axis = 0;
float E_axis = 0;
float newx = 0;
float newy = 0;

//Tell galileo how many motor shields and their I2C address
Adafruit_MotorShield AFMS_XY = Adafruit_MotorShield(0x61); //bottom stepper shield
Adafruit_MotorShield AFMS_Z = Adafruit_MotorShield(0x60);
Adafruit_MotorShield AFMS_E = Adafruit_MotorShield(0x63); 
 
 //Tell shield what stepper is connected to which port on each shield
Adafruit_StepperMotor *stepperX = AFMS_XY.getStepper(200, 1); // X stepper myStepper2
Adafruit_StepperMotor *stepperY = AFMS_XY.getStepper(200, 2); // Y stepper myStepper3
Adafruit_StepperMotor *stepperZ = AFMS_Z.getStepper(200, 2);// Z stepper shield myStepper5
Adafruit_StepperMotor *stepperE = AFMS_E.getStepper(200, 2);// E stepper shield myStepper5

//mac address of Galileo board
byte mac[] = {
  0x98, 0x4F, 0xEE, 0x05, 0xE8, 0x61
};
//Ip address of galileo
IPAddress ip(169,254,149,95);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
String HTTP_req;          // stores the HTTP request

int pinExtInt = 2; //external interupt pin.
int stopp=0; //flag to check for if interupt has been tripped.
int start = 0; // variable for triggering start of cycle.
 
volatile long lastButtonPush = 0; // volatile variable for change within the interuppt routine. 
 
void setup() {
  //start serial connection
  Serial.begin(9600);
  
  
  AFMS_XY.begin(); // Start the x,y stepper motor shield
  //AFMS_Z.begin();Start the Z axis stepper motor shield
  AFMS_E.begin(); // Start the Extruder stepper motor shield 
  
  //configure pins and enable the internal pull-up resistor
  pinMode(2, INPUT); // circuit has resistor in it
  pinMode(3, INPUT_PULLUP); // enable internal pull up resistor on galileo
  pinMode(4, INPUT_PULLUP); // enable internal pull up resistor on galileo
  pinMode(5, INPUT_PULLUP); // enable internal pull up resistor on galileo
  pinMode(6, INPUT_PULLUP); // enable internal pull up resistor on galileo
  pinMode(7, INPUT_PULLUP); // enable internal pull up resistor on galileo
  
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  attachInterrupt(pinExtInt, extIntISR, CHANGE);  // interupt setup
  fp = fopen("/home/root/happy2.txt", "r");  // open gcode file in linux memory
}

void loop() {
  establishContact();
  process_command();
  fclose(fp); //close file within linux memory
  Serial.print(" End; ");
}





 
 

    



