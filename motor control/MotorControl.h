#ifndef MotorH
#define MotorH

enum Direction {
	FORWARD,
	BACKWARD,
	STOP
};

class Motor {
public:

	Motor(int in1, int in2, int pwm);
	virtual ~Motor() {};


	void run(int speed, Direction direction) const;
	void stop() const;

private:
	int m_in1;
	int m_in2;
	int m_pwm;
};

#endif