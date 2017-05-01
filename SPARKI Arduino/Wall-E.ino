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
bool continuous = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //set on computer as COM9 for bluetooth
  Serial.println("Begin");
  AFMS.begin();
  myMotor->setSpeed(100); 
  myMotorTwo->setSpeed(100); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    input = Serial.readString();
    Serial.println(input);

  	int index = 0;
  
  	//Following section parses the input string to control what happens to the robot
  	index = input.indexOf(" "); //find the first occurence of a space
  	command = input.substring(0, index);
  	speed = input.substring(index + 1);
  	motorSpeed = speed.toInt();
  	myMotor->setSpeed(motorSpeed);
  	myMotorTwo->setSpeed(motorSpeed);
    Serial.print(command);
    Serial.println(" Success as parsed from arduino");

    /*This section is used for turning the robot left*/
    if(command == "leftC"){
      Serial.print(command);
      Serial.println(" has reached the execution loop");
      continuous = true;
      Serial.println("Continous has been set to true");
      myMotor->run(FORWARD);
      myMotorTwo->run(BACKWARD);
      command = "";
      while(continuous){
                
        while(input != "stopC"){
          if(Serial.available()> 0){
          input = Serial.readString();
          if(input == "stopC"){continuous = false;}
          }
        }
        Serial.println("Loop will exit");
      }
      Serial.println("Loop has exited");  
      myMotor->run(RELEASE);
      myMotorTwo->run(RELEASE);
	  }

   /*This section is used for turning the robot right*/
  	else if (command == "rightC") {
      continuous = true;
  		myMotor->run(BACKWARD);
  		myMotorTwo->run(FORWARD);
  		command = "";
      while(continuous){
                
        while(input != "stopC"){
          if(Serial.available()> 0){
          input = Serial.readString();
          if(input == "stopC"){continuous = false;}
          }
        }
        Serial.println("Loop will exit");
      }
      Serial.println("Loop has exited");
  		myMotor->run(RELEASE);
  		myMotorTwo->run(RELEASE);
  	}

   /*This section is used for moving the robot backwards*/
   else if (command == "backC") {
      continuous = true;
      myMotor->run(BACKWARD);
      myMotorTwo->run(BACKWARD  );
      command = "";
      while(continuous){
                
        while(input != "stopC"){
          if(Serial.available()> 0){
          input = Serial.readString();
          if(input == "stopC"){continuous = false;}
          }
        }
        Serial.println("Loop will exit");
      }
      Serial.println("Loop has exited");
      myMotor->run(RELEASE);
      myMotorTwo->run(RELEASE);
    }

   /*This section is used for turning the robot forward*/
   else if(command == "moveC"){
    Serial.print(command);
    Serial.println(" has reached the execution loop");
    continuous = true;
    Serial.println("Continous has been set to true");
    myMotor->run(FORWARD);
    myMotorTwo->run(FORWARD);
    command = "";
    while(continuous){
        
        while(input != "stopC"){
          if(Serial.available()> 0){
          input = Serial.readString();
          if(input == "stopC"){continuous = false;}
          }
       }
      Serial.println("Loop will exit");
    }
    Serial.println("Loop has exited");
    myMotor->run(RELEASE);
    myMotorTwo->run(RELEASE);
   }//end of movec condition
  }//end of if Serial.Available
 }//end of void loop

