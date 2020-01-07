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
        list<Sensor*> s1 = (*dev)->getSensors();

        for(list<Actuator*>::iterator act = a1.begin(); act != a1.end(); ++act)
        {
            string key = (*act)->getKey();

            if(!((*act)->getValue() == dat->readData(key)))
            {
                (*act)->setValue(dat->readData(key));
                (*dev)->sendMessage(dat->readData(key));
            }
        }   
        usleep(100000); // wait 100ms to prevent socket failure

        for(list<Sensor*>::iterator sens = s1.begin(); sens != s1.end(); ++sens)
        {
        	string key = (*sens)->getKey();
        	string buffer = (*dev)->receiveMessage();

        	string ID;
        	string Value;

//			for(int i = 0; i < buffer.length(); i++){
//				if(buffer[i] != ":"){
//					ID += buffer[i];
//				}else if(buffer[i] != ";")
//				{
//					Value += buffer[i];
//				}
//			}
        	// 01:1;02:879;
        	// receive sensor data

        	// identificeer key

        	// ken data van key to aan juiste sensor

        	// voer logic uit



        	// 21'31024'

        	if(!((*sens)->getValue() == dat->readData(key)))
        	{
        		(*sens)->
        				setValue(dat->readData(key));
        	}
        }
    }
}


