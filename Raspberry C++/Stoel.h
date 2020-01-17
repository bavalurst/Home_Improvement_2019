#ifndef STOEL_H
#define STOEL_H

#include "Device.h"
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

class Stoel : public Device
{
private:
    /* data */
	Actuator* a1;
	Actuator* a2;
	Sensor* s1;
	Sensor* s2;

	time_t timeStart;
	time_t alarm = 0;
	time_t cooldown = 0;
	int seizureAlert = 0;
	int previousPressure = 0;
	int currentPressure = 0;

	int oneSecond = 0;
	int seizureTime = 0;
	int seizureLevel = -1;
	int lastAct = 0;
public:
    Stoel(char*);
    virtual ~Stoel();
    virtual string logic(map<string, Device*>);
};

#endif /* STOEL_H */
