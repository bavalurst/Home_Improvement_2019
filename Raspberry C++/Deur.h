#ifndef DEUR_H
#define DEUR_H

#include "Device.h"
#include <ctime>
#include <string>
#include <iostream>

class Deur : public Device
{
private:
    /* Definieren van gebruikte variabelen in Deur.cpp */
	Actuator* a1;
	Actuator* a2;
	Actuator* a3;
	Actuator* a4;
	Actuator* a5;
	Actuator* a6;
	Actuator* a7;
	Actuator* a8;
	Actuator* a9;
	Sensor* s1;
	Sensor* s2;

	const char* PIN = "";
	int incorrectPinCount;
	string s = "";
	time_t timeStart;
	time_t timeDoorStart = NULL;

public:
    Deur(char*);
    virtual ~Deur();
    virtual string logic(map<string, Device*>);
    virtual string getStatus(string);
};

#endif /* DEUR_H */
