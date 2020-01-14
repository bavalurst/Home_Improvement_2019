#ifndef SCHEMERLAMP_H
#define SCHEMERLAMP_H

#include "Device.h"

class Schemerlamp : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;

public:
    Schemerlamp(char*);
    virtual ~Schemerlamp();
    virtual string logic(map<string, Device*>);
};

#endif /* SCHEMERLAMP_H */
