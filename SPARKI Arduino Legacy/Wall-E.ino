#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

//Various Declarations need in order to interface with motor shield and lcd display
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorTwo = AFMS.getMotor(4);
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

//Global Variables used during the program
String input = "";
int index = 0;
String command = ""; //stores the command string parsed from the input string
String speed = ""; //holds the speed value for the incoming speed command to be converted to motor speed
int motorSpeed = 175; //Max speed is 250
SoftwareSerial bSerial(0,1); //Creates the serial object using pins 0 and 1 instead of the on board BLE serial


void setup() {
  
  //Begins the setup for the LCD display
  lcd.begin(16, 2); //Initiates 16 characters on 2 lines
  lcd.print("Hello Good Sir!");

  //Beginst he serial communication
  Serial.begin(9600); //set on computer as COM9 for bluetooth
  Serial.println("Beginning Robot Control"); //Prints string to arduino serial monitor for debug
  bSerial.begin(9600); //begins Serial communication over the HC-06 bluetooth adapter

  //Initialization of motorshield
  AFMS.begin();
  myMotor->setSpeed(motorSpeed); 
  myMotorTwo->setSpeed(motorSpeed); 
}

void loop() {
  
  if(bSerial.available() > 0){
    input = bSerial.readString(); //records string value from the incoming bluetooth
    Serial.println(input); //Debug code to test what in comming string is
  	
    index = 0;
  	//Following section parses the input string to control what happens to the robot
  	index = input.indexOf(" "); //find the first occurence of a space
  	command = input.substring(0, index); //parses a string from the first word in the input

    /*This section sets the speed of the robot*/
    if(command == "setSpeed"){
    	speed = input.substring(index + 1); //parses the integer portion of the string command into a seperate string
    	motorSpeed = speed.toInt();
    	myMotor->setSpeed(motorSpeed);
    	myMotorTwo->setSpeed(motorSpeed);

      //Debug code to test what the parsed command and speed value
      Serial.print(command);
      Serial.println(" Success as parsed from arduino");
      Serial.println(motorSpeed);

      //Sets new message on the LCD panel
      lcd.setCursor(0,1); //moves text to beginning of second line
      lcd.print("                ");//clears and text already on the line
      lcd.setCursor(0,1); //moves back to beginning of line
      lcd.print("Speed set: ");
      lcd.print(motorSpeed);
    }

    /*This section is used for turning the robot left*/
    if(command == "leftC"){
      Serial.print(command);
      Serial.println(" has reached the execution loop");
      myMotor->run(FORWARD);
      myMotorTwo->run(BACKWARD);
      command = "";
    }
      
    /*This section of code stops all running motors*/  
    else if(input == "stopC"){
       Serial.print(command);
       Serial.println(" has reached the execution loop");
       myMotor->run(RELEASE);
       myMotorTwo->run(RELEASE);
    }
          
   /*This section is used for turning the robot right*/
  	else if (command == "rightC") {
  		Serial.print(command);
      Serial.println(" has reached the execution loop");
  		myMotor->run(BACKWARD);
  		myMotorTwo->run(FORWARD);
  		command = "";
  	}

   /*This section is used for moving the robot backwards*/
   else if (command == "backC") {
      Serial.print(command);
      Serial.println(" has reached the execution loop");
      myMotor->run(BACKWARD);
      myMotorTwo->run(BACKWARD);
      command = "";
   }

   /*This section is used for turning the robot forward*/
   else if(command == "moveC"){
    Serial.print(command);
    Serial.print(" has reached the execution loop and Robot should be moving with speed: ");
    Serial.println(motorSpeed);
    myMotor->run(FORWARD);
    myMotorTwo->run(FORWARD);
    command = "";
    
   }//end of movec condition
  }//end of if Serial.Available
 }//end of void loop

