#ifndef BED_H
#define BED_H

#include "Device.h"

class Bed : public Device
{
private:
	Actuator* a1;
	Sensor* s1;
	Sensor* s2;
public:
    Bed(char*);
    virtual ~Bed();
    virtual string logic(map<string, Device*>);
};

#endif /* BED_H */
