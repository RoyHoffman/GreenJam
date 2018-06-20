#ifndef SensorH
#define SensorH


class Sensor {
public:

	Sensor(int trigPin, int echoPin);
	virtual ~Sensor() {};


	float getDistance() const;

private:
	int m_trigPin;
	int m_echoPin;
};

#endif