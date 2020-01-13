#ifndef CONTROL_H
#define CONTROL_H

#include "Device.h"
#include "Bed.h"
#include "Stoel.h"
#include "Zuil.h"
#include "Schemerlamp.h"
#include "Fridge.h"
#include "Database.h"
#include "Actuator.h"
#include <list>
#include <map>

//class Database;

class Control
{
private:
    Database *dat;
    list<Device*> devices;
public:
    Control(/* args */);
    ~Control();
    void compareDatabaseToDevice();
    vector<string> parseMessage(string);
    void addDevice(Device*);
};

#endif /* CONTROL_H */
