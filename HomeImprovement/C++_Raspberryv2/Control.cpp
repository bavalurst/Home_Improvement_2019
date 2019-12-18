/*
 * Control.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Control.h"

Control::Control() 
{
	s1 = new Socket();

    Device *bed_dev = new Bed("10.42.0.123", s1, "bed");           // create new device
    addDevice(1, bed_dev);                                  // add device to map for devices

    dat = new Database();                     // create new database object
    //addDatabase(1, bed_dat);                                // add database object to map for databases

    Device *stoel_dev = new Stoel("10.42.0.170", s1, "stoel");       // create new device
    addDevice(2, stoel_dev);                                // add device to map for devices

    //Database *stoel_dat = new Database();                   // create new database object
    //addDatabase(2, stoel_dat);                              // add database object to map for databases
}       

Control::~Control()
{
	delete s1;
}

void Control::addDevice(int a, Device* d1)
{
    devices.insert(make_pair(a, d1));   // add device to map for devices
}

void Control::addDatabase(int b, Database* d2)
{
    databases.insert(make_pair(b, d2)); // add database object to map for databases
}

void Control::getData()
{
    // Get the data from all devices and put them in a map
    for (map<int, Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
        s1 = dev->second->getSocket();                  // get socket object, NOTE: Dit moet ik even met jullie overleggen, dus ga er nog niet mee kloten ^^
        s1->connectToServer(dev->second->getIP());      // connect device and PI with socket connection
        int a = s1->receiveMessage();                   // get data from device
        dev->second->setValue(a);                       // save data in the appriopriate device class
        s1->disconnect();                               // terminate socket connection
    }

    // get the data from a json file and put them in a map

    //int b = dat.getValue("bed");          // get data from json file, NOTE: Deze functie moet nog ingevuld worden, er staat nu fake data in
    //dat->second->setValue(b);                       // save data to database object

}

// deze functie gaat ervanuit dat de map van de databases de waarheid is 
// dit betekent dat als de waardes vergeleken worden, dat de devices aangepast worden op basis van de waardes van de databases
void Control::compareDatabaseToDevice()
{
    getData(); 

    // compare the values from the map with databases and the map from devices with each other, and act accordingly
    for (map<int, Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
    	string key = dev->second->getKey();


    	// compare values
        if(!(dat->readData(key) == dev->second->getValue()))
        {
            dev->second->logic();                       // deze functie moet nog geschreven worden
        	s1 = dev->second->getSocket();              
        	s1->connectToServer(dev->second->getIP());  // connect device and PI with socket connection
            s1->sendMessage();                          // send message to device
            s1->disconnect();                           // terminate socket connection
        }
        usleep(100000); // wait 100ms to prevent socket failure
    }
}

