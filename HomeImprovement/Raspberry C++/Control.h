/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#ifndef CONTROL_H
#define CONTROL_H

#include "Database.h"
#include "Device.h"
#include "Bed.h"

class Control
{
private:
    Socket *s1;
    map<int, Device*> devices;
    map<int, Database*> databases;
public:
    Control(/* args */);
    ~Control();
    void getData();
    void compareDatabaseToDevice();
    void addDevice(Device*);
    void addDatabase(Database*);
};

#endif /* CONTROL_H */
