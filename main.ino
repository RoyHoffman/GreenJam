#include <MotorControl.h>
#include <Vehicle.h>
#include <Sensor.h>

/*
SparkFun Inventor’s Kit
Circuit 5C - Autonomous Robot

This robot will drive around on its own and react to obstacles by backing up and turning to a new direction.
This sketch was adapted from one of the activities in the SparkFun Guide to Arduino.
Check out the rest of the book at
https://www.sparkfun.com/products/14326

This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
This code is completely free for any use.

View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/



//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor


//fron distance variables
const int FRONT_TRIG_PIN = 6;
const int FRONT_ECHO_PIN = 5;

//up distance variables
const int UP_TRIG_PIN = 3;
const int UP_ECHO_PIN = 2;


int switchPin = 7;             //switch to turn the robot on and off

float frontDistance = 0;            //variable to store the distance measured by the distance sensor
float upDistance = 0;            //variable to store the distance measured by the distance sensor

//robot behaviour variables
int backupTime = 300;           //amount of time that the robot will back up when it senses an object
int turnTime = 200;             //amount that the robot will turn once it has backed up

Sensor forwardSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
Sensor upSensor(UP_TRIG_PIN, UP_ECHO_PIN);

Motor right(AIN1, AIN2, PWMA);
Motor left(BIN1, BIN2, PWMB);
Vehicle marco(left, right);

/********************************************************************************/
void setup()
{
  pinMode(FRONT_TRIG_PIN, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(FRONT_ECHO_PIN, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor
  
  pinMode(UP_TRIG_PIN, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(UP_ECHO_PIN, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped


  //set the motor contro pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);                       //begin serial communication with the computer
  Serial.print("To infinity and beyond!");  //test the serial connection
}

/********************************************************************************/
void loop()
{
  //DETECT THE DISTANCE READ BY THE DISTANCE SENSOR
  frontDistance = forwardSensor.getDistance();
  upDistance = upSensor.getDistance();

  if(digitalRead(switchPin) == LOW){  //if the on switch is flipped

    if(frontDistance < 10){                //if an object is detected
      //back up and turn
      Serial.print(" ");
      Serial.print("BACK!");

      //stop for a moment
      marco.stop();
      delay(200);

      //back up
      marco.backward(255, backupTime);

    }else{                         //if no obstacle is detected drive forward
      Serial.print(" ");
      Serial.print("Moving...");

      marco.forward(255);
    }
  } else{                         //if the switch is off then stop

      //stop the motors
      marco.stop();
  }

  delay(50);                      //wait 50 milliseconds between readings
}
