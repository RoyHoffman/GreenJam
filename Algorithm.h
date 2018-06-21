#ifndef AlgoH
#define AlgoH

#include "Vehicle.h"
#include "Sensor.h"

class Marco : public Vehicle {
public:
	Marco(const Motor& leftMotor, const Motor& rightMotor, 
		const Sensor& upSensor, const Sensor& forwardSensor);
	bool findhide();
	bool findhide2();
	bool CheckOverTime(int& counter,int counterCheck,const int& maxCheck,int& value, char c );

private:
	Sensor m_upSensor;
	Sensor m_forwardSensor;
	//Sensor m_sideSensor;

	int m_hightCounter;
	int m_distCounter;

	int m_highCounterHigh;
	int m_highCounterLow;

	int m_forwardSpeed;
};

#endif	