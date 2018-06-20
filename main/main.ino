#include <MotorControl.h>
#include <Vehicle.h>


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
  frontDistance = getFrontDistance();
  upDistance = getUpDistance();

  if(digitalRead(switchPin) == LOW){  //if the on switch is flipped

    if(frontDistance < 10){                //if an object is detected
      //back up and turn
      Serial.print(" ");
      Serial.print("BACK!");

      //stop for a moment
//      rightMotor(0);
//      leftMotor(0);
//      delay(200);
      marco.stop();
      delay(200);

      //back up
//      rightMotor(-255);
//      leftMotor(-255);
//      delay(backupTime);
      marco.backward(255, backupTime);

      //turn away from obsticle 
//      rightMotor(255);
//      leftMotor(-255);    
//      delay(turnTime);
//      marco.right(255, turnTime);

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

void runMotor(int motorSpeed, int in1, int in2, int pwm) {
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(in1, HIGH);                         //set pin 1 to high
    digitalWrite(in2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backwar (negative speed)
  {
    digitalWrite(in1, LOW);                          //set pin 1 to low
    digitalWrite(in2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(in1, LOW);                          //set pin 1 to low
    digitalWrite(in2, LOW);                          //set pin 2 to low
  }
  analogWrite(pwm, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  runMotor(motorSpeed, AIN1, AIN2, PWMA);
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  runMotor(motorSpeed, BIN1, BIN2, PWMB);
}

/********************************************************************************/
//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance(int trigPin, int echoPin)
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calcualtedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calcualtedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calcualtedDistance;              //send back the distance that was calculated
}

float getFrontDistance() {
  return getDistance(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
}

float getUpDistance() {
  return getDistance(UP_TRIG_PIN, UP_ECHO_PIN);
}


