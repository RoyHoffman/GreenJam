#include "Arduino.h"
#include "Vehicle.h"

const int Vehicle::DURATION_INFINITY = -1;
const int backupTime = 300;           //amount of time that the robot will back up when it senses an object
const int turnTime = 1000;             //amount that the robot will turn once it has backed up


Vehicle::Vehicle(const Motor& leftMotor, const Motor& rightMotor) :
	m_leftMotor(leftMotor),
	m_rightMotor(rightMotor) { };


void Vehicle::forward(int speed, int duration) const {
	m_rightMotor.run(speed, Direction::FORWARD);
	m_leftMotor.run(speed, Direction::FORWARD);
	stopAfterDuration(duration);
}

void Vehicle::backward(int speed, int duration) const {
	m_rightMotor.run(speed, Direction::BACKWARD);
	m_leftMotor.run(speed, Direction::BACKWARD);
	stopAfterDuration(duration);
}

void Vehicle::right(int speed, int duration) const {
	m_rightMotor.run(speed, Direction::FORWARD);
	m_leftMotor.run(speed, Direction::BACKWARD);
	stopAfterDuration(duration);
}

void Vehicle::left(int speed, int duration) const {
	m_rightMotor.run(speed, Direction::BACKWARD);
	m_leftMotor.run(speed, Direction::FORWARD);
	stopAfterDuration(duration);
}

void Vehicle::stopAfterDuration(int duration) const {	
  if (duration != Vehicle::DURATION_INFINITY) {
    delay(duration);
		m_rightMotor.stop();
		m_leftMotor.stop();
  }
}

void Vehicle::stop() const {
		m_rightMotor.stop();
		m_leftMotor.stop();
}

void Vehicle::turnBack() const {
	stop();
  delay(500);
	backward(255,backupTime);
  right(255,turnTime);
  stop();
  delay(500);
  forward(255);
}