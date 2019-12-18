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
    	int key = (*dev)->getActuator()->getKey();

        if(key == dat->readData(key))
        {
            cout << "Value id " << (*dev)->getActuator()->getKey() << " : " << (*dev)->getActuator()->getValue() << endl;
        }else
        {
            cout << "Not found" << endl;
        }
        
        usleep(100000); // wait 100ms to prevent socket failure
    }
}

