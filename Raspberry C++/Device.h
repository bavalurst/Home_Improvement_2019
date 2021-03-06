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
#include <map>

#include "Actuator.h"
#include "Sensor.h"

using namespace std;

class Device
{
private:
    char* ip_addr;
    int sock = 0;
    int PORT = 3000;
    int valread = 0;
    int num = 0;
    const char *data;;
    char buffer[25] = {0};
    map<string, Actuator*> actuatorId;
    map<string, Sensor*> sensorId;
//    Actuator *a1;
public:
    Device(char*);
    virtual ~Device();
    virtual char* getIP();
    virtual int sendMessage(string);
    virtual string receiveMessage();
    virtual map<string, Actuator*> getActuators();
    virtual map<string, Sensor*> getSensors();
    virtual void addActuator(string, Actuator*);
    virtual void addSensor(Sensor*);
    virtual string logic(map<string, Device*>) = 0;
    virtual string getStatus(string) = 0;
};

#endif /* Device_H */
