/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <map>
#include <string>

#include "Socket.h"

using namespace std;

class Device
{
private:
    int value = 0;
    char* ip_addr;
    Socket *s1;
public:
    Device(char*, Socket*);
    virtual ~Device();
    virtual char* getIP();
    virtual void setValue(int);
    virtual int getValue();
    virtual Socket* getSocket();
    virtual void logic() = 0;
};

#endif /* Device_H */
