#ifndef SCHEMERLAMP_H
#define SCHEMERLAMP_H

#include "Device.h"
#include <vector>
#include <string>

class Schemerlamp : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;
	time_t CurrentTime;
	time_t AlarmTime;
	int fluctuations;
	vector<int>AlarmReading;

public:
    Schemerlamp(char*);
    virtual ~Schemerlamp();
    virtual string logic(map<string, Device*>);
};

#endif /* SCHEMERLAMP_H */
