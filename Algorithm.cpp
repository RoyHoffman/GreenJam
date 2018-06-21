#include "Algorithm.h"
#include "Arduino.h"

const int NOISE_FILTER = 6;

const int hideUpDistance = 60;
const int hitDistance = 10;
const int slowDistance = 50;
const int delayTime = 100;

const int MAX_SPEED = 255;
const int SLOW_SPEED = 100;
int test(){
	return 5;
}
bool Marco::CheckOverTime(int& counter,int counterCheck,const int& maxCheck,int& value, char c){
	if(c=='h'){
			Serial.println(value);
		}
	if(value < maxCheck && ( value != 0) ){

		counter++;
		if (counter > counterCheck)
			return true;
	}
	else {
		counter = 0;
	}
	return false;
}
Marco::Marco(const Motor& leftMotor, const Motor& rightMotor,
	const Sensor& upSensor, const Sensor& forwardSensor) :
Vehicle(leftMotor, rightMotor),
m_upSensor(upSensor), m_forwardSensor(forwardSensor),
m_forwardSpeed(MAX_SPEED) {}

bool Marco::findhide() {
    int x = m_upSensor.getDistance();

    //Serial.println(x);
    int y = m_forwardSensor.getDistance();
    if(x < hideUpDistance && x != 0) {
    	m_hightCounter++;
    	Serial.print(m_hightCounter);
    	Serial.print(" UPPP ");
    	Serial.println(x);
    	if (m_hightCounter > NOISE_FILTER * 2) {
	      forward(100, delayTime);
	      return true;	
    	}
    }
    else {
  		m_hightCounter = 0;
  	}

  	if (y < slowDistance && y != 0) {
  		m_forwardSpeed = SLOW_SPEED; 
  	} else {
  		m_forwardSpeed = MAX_SPEED;
  	}

    if (y < hitDistance && y != 0) {
    	m_distCounter++;
    	Serial.print(m_distCounter);
    	Serial.print(" FRONTTT ");
    	Serial.println(y);
      if (m_distCounter > NOISE_FILTER / 2) {
      	turnBack();
    	}
    	return false;
    }
		else {
			m_distCounter = 0;
		}

    forward(m_forwardSpeed);
    return false;
}

const int hideUpDistanceHigh = 80;
const int hideUpDistanceLow = 50;


bool Marco::findhide2() {
		findhide2();
		static int hightCounterLow = 0;
		static int hightCounterHigh = 0;

      int x = m_upSensor.getDistance();

    //Serial.println(x);
    int y = m_forwardSensor.getDistance();
    //Serial.println(x);

    if (CheckOverTime(hightCounterLow,NOISE_FILTER*2,hideUpDistanceLow,x,'u')){
	      forward(100, delayTime);
	      return true;	
    }
    	if (y < slowDistance && y != 0) {
  		m_forwardSpeed = SLOW_SPEED; 
  	} else {
  		m_forwardSpeed = MAX_SPEED;
  	}

    if(CheckOverTime(hightCounterHigh,NOISE_FILTER*2,hideUpDistanceHigh,x,'h')&&
    	CheckOverTime(m_distCounter,NOISE_FILTER/2,hitDistance,y,'d')){
    	forward(100, delayTime);
	     return true;	
    }




		if(CheckOverTime(m_distCounter,NOISE_FILTER/2,hitDistance,y,'b')){
			turnBack();
		}

    forward(m_forwardSpeed);
    return false;
}

