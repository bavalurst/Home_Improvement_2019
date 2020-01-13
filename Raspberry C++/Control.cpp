#include "Control.h"

Control::Control() 
{
    dat = new Database();                     // create new database object

    Device *bed = new Bed("10.42.0.170");           // create new device
    addDevice(bed);

    //Device *stoel = new Stoel("10.42.0.10");
    //addDevice(stoel);// add device to map for devices

    //Device *zuil = new Zuil("10.42.0.178");
    //addDevice(zuil); // add zuil

    //Device *schemerlamp = new Schemerlamp("10.42.0.137");
    //addDevice(schemerlamp); // add schemerlamp

    //Device *fridge = new Fridge("10.42.0.187");
    //addDevice(fridge); // add fridge
}       

Control::~Control()
{
    delete dat;
}

void Control::addDevice(Device* d1)
{
    devices.push_back(d1);
}


void Control::compareDatabaseToDevice()
{   
    // compare the values from the map with databases and the map from devices with each other, and act accordingly
    for (list<Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
        list<Actuator*> a1 = (*dev)->getActuators();
        map<string, Sensor*> sensors;
        map<string, Sensor*>::iterator it;
        sensors = (*dev)->getSensors();

        for(list<Actuator*>::iterator act = a1.begin(); act != a1.end(); ++act)
        {
            string key = (*act)->getKey();

            if(!((*act)->getValue() == dat->readActuatorData(key)))
            {
            	(*act)->setValue(dat->readActuatorData(key));
                (*dev)->sendMessage(dat->readActuatorData(key));
            }
        }

        usleep(100000); // wait 100ms to prevent socket failure


        string buffer = (*dev)->receiveMessage();
        vector<string> result;
        result = parseMessage(buffer);

        for(int i=0; i < result.size(); i+=2)
        	{
        		it = sensors.find(result[i]);

        		if(it != sensors.end()) {
        			it->second->setValue(result[i + 1]);
        			dat->updateSensorData(result[i], result[i + 1]);
        			cout << "Updating with key: " << result[i] << " Value: " << result[i+1] << endl;
        		}
            }

        (*dev)->logic();

     }
}


vector<string> Control::parseMessage(string message)
{

  vector<string> stringlist;
  string result;
  string result2;
  string temp;


  int i;

  for (i=0; i != sizeof(message); i++)   {

    if (!(message[i] == ';' || message[i] == ':'))
    temp += message[i];

    else {
        stringlist.push_back(temp);
        temp = "";
    }

    }

	return stringlist;

}


