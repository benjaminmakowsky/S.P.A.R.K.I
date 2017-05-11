#include <CurieBLE.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

BLEPeripheral blePeripheral; //creates a bluetooth object
BLEService motorService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharCharacteristic directionCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead|BLEWrite);

//BLECharacteristic directionCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead|BLEWrite, 10);
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //creates adafruit motorshield object
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //creates a motor
Adafruit_DCMotor *myMotorTwo = AFMS.getMotor(4); //creates the second motor

String input = ""; //incoming string
String command = ""; //command string
String speed = ""; //string to hold speed 
int motorSpeed = 0; //Max speed is 255
int control = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //set on computer as COM? for bluetooth
  Serial.println("Begin"); //begins communication with serial
  AFMS.begin(); //starts the motor shield
  myMotor->setSpeed(210); //sets initial speed
  myMotorTwo->setSpeed(210); //sets initial speed

 /*Bluetooth setup*/
blePeripheral.setLocalName("SPARKI"); //name to be displayed on bluetooth finder
blePeripheral.setDeviceName("SPARKI");
blePeripheral.setAdvertisedServiceUuid(motorService.uuid());
blePeripheral.addAttribute(motorService);
blePeripheral.addAttribute(directionCharacteristic);
directionCharacteristic.setEventHandler(BLEWritten, directionCharacterisiticWritten);
blePeripheral.begin();
  
  
}

void loop() {

   blePeripheral.poll();
    
}//end of void loop

void directionCharacterisiticWritten(BLECentral& central, BLECharacteristic& characteristic){
  Serial.print("Charactersitic event, written: ");
  Serial.println(directionCharacteristic.value());
  if(directionCharacteristic.value()){
    
    input = directionCharacteristic.value();
    Serial.print("Input Value: ");
    Serial.println(input);
    //Following section parses the input string to control what happens to the robot
    int index = 0;
    index = input.indexOf(" "); //find the first occurence of a space
    command = input.substring(0, 1); //parses a string from the first word in the input
    Serial.print("Comamnd is: ");
    Serial.println(command);

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
      if(command == "l"){
        Serial.print(command);
        Serial.println(" has reached the execution loop");
        myMotor->run(FORWARD);
        myMotorTwo->run(BACKWARD);
        command = "";
      }
        
      /*This section of code stops all running motors*/  
      else if(command == "s"){
         Serial.print(command);
         Serial.println(" has reached the execution loop");
         myMotor->run(RELEASE);
         myMotorTwo->run(RELEASE);
      }
            
     /*This section is used for turning the robot right*/
      else if (command == "r") {
        Serial.print(command);
        Serial.println(" has reached the execution loop");
        myMotor->run(BACKWARD);
        myMotorTwo->run(FORWARD);
        command = "";
      }
  
     /*This section is used for moving the robot backwards*/
     else if (command == "b") {
        Serial.print(command);
        Serial.println(" has reached the execution loop");
        myMotor->run(BACKWARD);
        myMotorTwo->run(BACKWARD);
        command = "";
     }
  
     /*This section is used for turning the robot forward*/
     else if(command == "f"){
      Serial.print(command);
      Serial.println(" has reached the execution loop");
      myMotor->run(FORWARD);
      myMotorTwo->run(FORWARD);
      command = "";
     }//end of movec condition
  }
}

  


