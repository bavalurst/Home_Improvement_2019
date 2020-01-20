#ifndef DEUR_H
#define DEUR_H

#include "Device.h"

class Deur : public Device
{
private:
    /* Definieren van gebruikte variabelen in Deur.cpp */
	Actuator* a0;
	Actuator* a1;
	Actuator* a2;
	Actuator* a3;
	Actuator* a4;
	Actuator* a5;
	Actuator* a6;
	Actuator* a7;
	Actuator* a8;
	Sensor* s1;
	Sensor* s2;

	string PIN = "";
	int incorrectPinCount = "0";
	string s = "";
	time_t timeStart;

public:
    Deur(char*);
    virtual ~Deur();
    virtual string logic(map<string, Device*>);
};

#endif /* DEUR_H */
