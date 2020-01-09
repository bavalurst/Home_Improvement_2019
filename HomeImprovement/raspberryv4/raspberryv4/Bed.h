#ifndef BED_H
#define BED_H

#include "Device.h"

class Bed : public Device
{
private:
	Actuator* a1;
	Sensor* s1;
public:
    Bed(char*);
    virtual ~Bed();
    virtual void logic();
};

#endif /* BED_H */
