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
	Actuator* a3;
	Sensor* s1;
	Sensor* s2;
public:
    Venster(char*);
    virtual ~Venster();
    virtual string logic(map<string, Device*>);
    virtual string getStatus(string);
};

#endif /* STOEL_H */
