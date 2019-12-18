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
#include "Stoel.h"

class Control
{
private:
    Socket *s1;
    map<int, Device*> devices;
    map<int, Database*> databases;
    Database* dat;
public:
    Control(/* args */);
    ~Control();
    void getData();
    void compareDatabaseToDevice();
    void addDevice(int, Device*);
    void addDatabase(int, Database*);
};

#endif /* CONTROL_H */
