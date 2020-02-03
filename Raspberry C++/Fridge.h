#ifndef FRIDGE_H
#define FRIDGE_H

#include "Device.h"
#include <ctime>
#include <iostream>

using namespace std;

class Fridge : public Device
{
private:
    /* data */
	Actuator* a1;
	Sensor* s1;
	Sensor* s2;
	Sensor* s3;
	time_t timeStart;
	int fridgeLimit = 10;
	int deurOpen;
public:
    Fridge(char*);
    virtual ~Fridge();
    virtual string logic(map<string, Device*>);
    virtual string getStatus(string);
};

#endif /* FRIDGE_H */
