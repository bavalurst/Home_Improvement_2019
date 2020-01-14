#ifndef STOEL_H
#define STOEL_H

#include "Device.h"

class Stoel : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;

public:
    Stoel(char*);
    virtual ~Stoel();
    virtual string logic(map<string, Device*>);
};

#endif /* STOEL_H */
