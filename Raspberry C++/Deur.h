#ifndef DEUR_H
#define DEUR_H

#include "Device.h"

class Deur : public Device
{
private:
<<<<<<< HEAD
    /* Definieren van gebruikte variabelen in Deur.cpp */
=======
    /* data */
>>>>>>> bbe3ea851ba00163bfa6e6f34f9cb53c8858f9c6
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

<<<<<<< HEAD
	string PIN = "";
=======
	int PIN = "";
>>>>>>> bbe3ea851ba00163bfa6e6f34f9cb53c8858f9c6
	int incorrectPinCount = "0";
	string s = "";
	time_t timeStart;

public:
    Deur(char*);
    virtual ~Deur();
    virtual string logic(map<string, Device*>);
};

#endif /* DEUR_H */
