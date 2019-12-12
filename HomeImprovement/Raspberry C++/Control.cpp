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

    Device *bed_dev = new Bed(1, "10.42.0.123", s1);
    addDevice(bed_dev);

    Database *bed_dat = new Database(1);
    addDatabase(bed_dat);
}

Control::~Control()
{

	delete s1;
}

void Control::addDevice(Device* d1)
{
    devices.insert(make_pair(d1->getKey(), d1));
}

void Control::addDatabase(Database* d2)
{
    databases.insert(make_pair(d2->getKey(), d2));
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

    map<int, Device*>::iterator dev = devices.begin();

    for (map<int, Database*>::iterator dat = databases.begin(); dat != databases.end(); ++dat)
    {
        if(!(dat->second->getKey() == dev->second->getKey() && dat->second->getValue() == dev->second->getValue()))  // change key later on
        {
            dev->second->logic();
        	s1 = dev->second->getSocket();
        	s1->connectToServer(dev->second->getIP());
            s1->sendMessage();
            s1->disconnect();
        }
        dev++;
    }
}

