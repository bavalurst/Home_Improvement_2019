#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <list>

#include "Actuator.h"

#define PORT 3000

using namespace std;

class Device
{
private:
    char* ip_addr;
    int sock = 0;
    int valread = 0;
    int num = 0;
    char *data = "7";
    char buffer[4] = {0};
    Actuator *a1;
    list<Actuator*> id;
public:
    Device(char*);
    virtual ~Device();
    virtual char* getIP();
    virtual int sendMessage();
    virtual int receiveMessage();
    virtual list<Actuator*> getActuators();
    virtual void logic() = 0;
};

#endif /* Device_H */
