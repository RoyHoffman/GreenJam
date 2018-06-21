
// include core Wiring API
#include "Arduino.h"
#include "MotorControl.h"

Motor::Motor(int in1, int in2, int pwm) :
m_in1(in1), m_in2(in2), m_pwm(pwm) {

}

void Motor::run(int speed, Direction direction) const {
  if (direction ==  Direction::FORWARD)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(m_in1, HIGH);                         //set pin 1 to high
    digitalWrite(m_in2, LOW);                          //set pin 2 to low
  }
  else if (direction ==  Direction::BACKWARD)                            //if the motor should drive backwar (negative speed)
  {
    digitalWrite(m_in1, LOW);                          //set pin 1 to low
    digitalWrite(m_in2, HIGH);                         //set pin 2 to high
  }
  else if (direction ==  Direction::STOP)                                                //if the motor should stop
  {
    digitalWrite(m_in1, LOW);                          //set pin 1 to low
    digitalWrite(m_in2, LOW);                          //set pin 2 to low
  }

  analogWrite(m_pwm, abs(speed));                 //now that the motor direction is set, drive it at the entered speed
  
}

void Motor::stop() const {
  run(0, Direction::STOP);
}