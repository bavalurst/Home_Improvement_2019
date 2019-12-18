#ifndef CONTROL_H
#define CONTROL_H

#include "Device.h"
#include "Bed.h"
#include "Stoel.h"
#include "Database.h"
#include "Actuator.h"
#include <list>

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
    void addDevice(Device*);
};

#endif /* CONTROL_H */
