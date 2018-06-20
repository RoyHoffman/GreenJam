// include core Wiring API
#include "Arduino.h"
#include "Sensor.h"

Sensor::Sensor(int trigPin, int echoPin) :
	m_trigPin(trigPin),
	m_echoPin(echoPin) { };


float Sensor::getDistance() const {
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calcualtedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(m_trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(m_trigPin, LOW);

  echoTime = pulseIn(m_echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calcualtedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calcualtedDistance;              //send back the distance that was calculated
}