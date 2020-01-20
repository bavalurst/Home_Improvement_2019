#ifndef DEUR_H
#define DEUR_H

#include "Device.h"

class Deur : public Device
{
private:
    /* data */
	Actuator* a1;
	Actuator* a2;
	Actuator* a3;
	Actuator* a4;
	Sensor* s1;
	Sensor* s2;

	string s = "";

public:
    Deur(char*);
    virtual ~Deur();
    virtual string logic(map<string, Device*>);
};

#endif /* DEUR_H */
