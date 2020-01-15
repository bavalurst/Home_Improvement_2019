#ifndef BED_H
#define BED_H

#include "Device.h"
#include <ctime>
#include <iostream>

using namespace std;

class Bed : public Device
{
private:
	Actuator* a1;
	Sensor* s1;
	Sensor* s2;
	time_t timeStart;
	bool goSleep = 0;
	bool alarm = 0;
public:
    Bed(char*, time_t);
    virtual ~Bed();
    virtual string logic(map<string, Device*>);
};

#endif /* BED_H */
