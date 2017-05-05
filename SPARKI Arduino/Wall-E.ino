#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorTwo = AFMS.getMotor(4);


String input = "";
String command = "";
String speed = "";
int motorSpeed = 0; //Max speed is 255
//bool continuous = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //set on computer as COM9 for bluetooth
  Serial.println("Begin");
  AFMS.begin();
  myMotor->setSpeed(175); 
  myMotorTwo->setSpeed(175); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    input = Serial.readString();
    Serial.println(input);

  	int index = 0;
  
  	//Following section parses the input string to control what happens to the robot
  	index = input.indexOf(" "); //find the first occurence of a space
  	command = input.substring(0, index); //parses a string from the first word in the input

    /*This section sets the speed of the robot*/
    if(command == "setSpeed"){
    	speed = input.substring(index + 1);
    	motorSpeed = speed.toInt();
    	myMotor->setSpeed(motorSpeed);
    	myMotorTwo->setSpeed(motorSpeed);
      Serial.print(command);
      Serial.println(" Success as parsed from arduino");
      Serial.println(motorSpeed);
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
      myMotorTwo->run(BACKWARD  );
      command = "";
   }

   /*This section is used for turning the robot forward*/
   else if(command == "moveC"){
    Serial.print(command);
    Serial.println(" has reached the execution loop");
    myMotor->run(FORWARD);
    myMotorTwo->run(FORWARD);
    command = "";
    
   }//end of movec condition
  }//end of if Serial.Available
 }//end of void loop

