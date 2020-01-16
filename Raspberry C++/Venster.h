#ifndef VENSTER_H
#define VENSTER_H

#include "Device.h"
#include <ctime>
#include <iostream>

class Venster : public Device
{
private:
    /* data */
	Actuator* a1;
	Actuator* a2;
	Sensor* s1;
	Sensor* s2;
public:
    Venster(char*);
    virtual ~Venster();
    virtual string logic(map<string, Device*>);
};

#endif /* STOEL_H */
