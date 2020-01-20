#ifndef CONTROL_H
#define CONTROL_H

#include "Device.h"
#include "Bed.h"
#include "Stoel.h"
#include "Zuil.h"
#include "Deur.h"
#include "Schemerlamp.h"
#include "Fridge.h"
#include "Database.h"
#include "Actuator.h"
#include <iostream>
#include <list>
#include <ctime>
#include <map>

using namespace std;
//class Database;

class Control
{
private:
    Database *dat;
    map<string, Device*> devices;
    time_t Time = time(nullptr);
    time_t medicIntakeTime = 0;
public:
    Control(/* args */);
    ~Control();
    void compareDatabaseToDevice();
    vector<string> parseMessage(string);
    void addDevice(string, Device*);
    void medicine();
};

#endif /* CONTROL_H */
