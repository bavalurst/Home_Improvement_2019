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
#include "Sensor.h"

#define PORT 3000

using namespace std;

class Device
{
private:
    char* ip_addr;
    int sock = 0;
    int valread = 0;
    int num = 0;
    const char *data;;
    char buffer[1024] = {0};
    list<Actuator*> actuatorId;
    list<Sensor*> sensorId;
//    Actuator *a1;
public:
    Device(char*);
    virtual ~Device();
    virtual char* getIP();
    virtual int sendMessage(string);
    virtual string receiveMessage();
    virtual list<Actuator*> getActuators();
    virtual list<Sensor*> getSensors();
    virtual void addActuator(Actuator*);
    virtual void addSensor(Sensor*);
    virtual void logic() = 0;
};

#endif /* Device_H */
