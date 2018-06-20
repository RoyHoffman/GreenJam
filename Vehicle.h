#ifndef VehicleH
#define VehicleH

#include "MotorControl.h"

class Vehicle {
public:
	static const int DURATION_INFINITY;

	Vehicle(const Motor& leftMotor, const Motor& rightMotor);
	virtual ~Vehicle() {};

	void forward(int speed, int duration=Vehicle::DURATION_INFINITY) const;
	void backward(int speed, int duration=Vehicle::DURATION_INFINITY) const;
	void right(int speed, int duration=Vehicle::DURATION_INFINITY) const;
	void left(int speed, int duration=Vehicle::DURATION_INFINITY) const;
	void stop() const;

private:
	void stopAfterDuration(int duration) const;

	Motor m_leftMotor;
	Motor m_rightMotor;
};

#endif