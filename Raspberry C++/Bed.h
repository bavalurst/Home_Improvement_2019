#ifndef BED_H
#define BED_H

#include "Device.h"
#include <ctime> // Hiermee kan time (secondes na 1 jan. 1970) verwerkt worden naar gewenste datum- en tijdsformaat
#include <iostream>

using namespace std;

class Bed : public Device
{
private:
	Actuator* a1; // actuatoren
	Sensor* s1; // sensoren
	Sensor* s2;
	time_t timeStart; // timeStart (Hiermee kan een soort stopwatch gemaakt worden door huidige tijd met deze waarde te vergelijken)
	bool goSleep = 0; // Gebruikt om bedtijd en opstaantijd apart te doorlopen
	bool alarm = 0; // of het alarm aanstaan of niet

	int oneSecond = 0; // één seconde later dan timeStart
	int seizureTime = 0; // binnen welke tijd in secondes er op afwijkingen in druk gemeten moet worden
	int seizureLevel = -1; // hoeveel grote drukverschillen er hebben plaatsgevonden
	int lastAct = 0; // laatste waarde van druksensor
public:
    Bed(char*);
    virtual ~Bed();
    virtual string logic(map<string, Device*>);
};

#endif /* BED_H */
