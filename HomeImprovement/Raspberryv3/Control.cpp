#include "Control.h"

Control::Control() 
{
    dat = new Database();                     // create new database object

    Device *bed = new Bed("10.42.0.123");           // create new device
    addDevice(bed);                                         // add device to map for devices
}       

Control::~Control()
{
    delete dat;
}

void Control::addDevice(Device* d1)
{
    devices.push_back(d1);
}

// deze functie gaat ervanuit dat de map van de databases de waarheid is 
// dit betekent dat als de waardes vergeleken worden, dat de devices aangepast worden op basis van de waardes van de databases
void Control::compareDatabaseToDevice()
{   
    // compare the values from the map with databases and the map from devices with each other, and act accordingly
    for (list<Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
        list<Actuator*> a1 = (*dev)->getActuators();

        for(list<Actuator*>::iterator act = a1.begin(); act != a1.end(); ++act)
        {
            string key = (*act)->getKey();
            string value = dat->readData(key);

            if(!((*act)->getValue() == dat->readData(key)))
            {
                (*act)->setValue(value);
                (*dev)->sendMessage(value);
            }
            usleep(50000); // wait 100ms to prevent socket failure
        }   
    }
}

