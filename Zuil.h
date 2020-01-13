#ifndef ZUIL_H
#define ZUIL_H

#include "Device.h"

class Zuil : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;

public:
    Zuil(char*);
    virtual ~Zuil();
    virtual void logic();
};

#endif /* ZUIL_H */
