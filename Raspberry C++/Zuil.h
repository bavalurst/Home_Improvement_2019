#ifndef ZUIL_H
#define ZUIL_H

#include "Device.h"

class Zuil : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;
	Sensor* s2;

public:
    Zuil(char*);
    virtual ~Zuil();
    virtual string logic(map<string, Device*>);
};

#endif /* ZUIL_H */
