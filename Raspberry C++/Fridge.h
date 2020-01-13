#ifndef FRIDGE_H
#define FRIDGE_H

#include "Device.h"

class Fridge : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;

public:
    Fridge(char*);
    virtual ~Fridge();
    virtual void logic();
};

#endif /* FRIDGE_H */
