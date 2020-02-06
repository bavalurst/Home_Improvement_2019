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
    /* Definieren van gebruikte variabelen in Stoel.cpp */
	Actuator* a1;
	Actuator* a2;
	Actuator* a3;
	Sensor* s1;
	Sensor* s2;

	time_t timeStart;
	time_t alarm = NULL;
	time_t cooldown = NULL;
	time_t switchTimer = NULL;
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
    virtual string getStatus(string);
};

#endif /* STOEL_H */
