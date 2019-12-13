/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Control.h"

Control::Control() 
{
	s1 = new Socket();

    Device *bed_dev = new Bed("10.42.0.123", s1);
    addDevice(1, bed_dev);

    Database *bed_dat = new Database();
    addDatabase(1, bed_dat);

    Device *stoel_dev = new Stoel("10.42.0.170", s1);
    addDevice(2, stoel_dev);

    Database *stoel_dat = new Database();
    addDatabase(2, stoel_dat);
}

Control::~Control()
{

	delete s1;
}

void Control::addDevice(int a, Device* d1)
{
    devices.insert(make_pair(a, d1));
}

void Control::addDatabase(int b, Database* d2)
{
    databases.insert(make_pair(b, d2));
}

void Control::getData()
{
    for (map<int, Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
        s1 = dev->second->getSocket();
        s1->connectToServer(dev->second->getIP());
        int a = s1->receiveMessage();
        dev->second->setValue(a);
        s1->disconnect();
    }

    for (map<int, Database*>::iterator dat = databases.begin(); dat != databases.end(); ++dat)
    {
        int b = dat->second->receiveMessage();
        dat->second->setValue(b);
    }
}

void Control::compareDatabaseToDevice()
{
    getData();

    for (map<int, Database*>::iterator dat = databases.begin(); dat != databases.end(); ++dat)
    {
    	map<int, Device*>::iterator dev = devices.find(dat->first);
        if(!(dat->second->getValue() == dev->second->getValue()))  // change key later on
        {
            dev->second->logic();
        	s1 = dev->second->getSocket();
        	s1->connectToServer(dev->second->getIP());
            s1->sendMessage();
            s1->disconnect();
        }
        usleep(100000);
    }
}

