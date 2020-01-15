#include "Control.h"

Control::Control() 
{
	time_t Time = time(nullptr); //Ask for the time once (for bed)
    dat = new Database();                     // create new database object

    Device *bed = new Bed("10.42.0.170", Time);           // create new device
    addDevice("Bed", bed);

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

void Control::addDevice(string key, Device* d1)
{
    devices.insert(make_pair(key, d1));
}


void Control::compareDatabaseToDevice()
{   
    // compare the values from the map with databases and the map from devices with each other, and act accordingly
    for (map<string, Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
        map<string, Actuator*> a1 = dev->second->getActuators();
        map<string, Sensor*> sensors;
        map<string, Sensor*>::iterator it;
        sensors = dev->second->getSensors();

        for(map<string, Actuator*>::iterator act = a1.begin(); act != a1.end(); ++act)
        {
            string key = act->first;

            if(!(act->second->getValue() == dat->readActuatorData(key)))
            {
            	act->second->setValue(dat->readActuatorData(key));
                dev->second->sendMessage(act->second->getKey() + dat->readActuatorData(key));
            }
        }

        usleep(100000); // wait 100ms to prevent socket failure

        string buffer = dev->second->receiveMessage();
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

        string SaveThis = dev->second->logic(devices);
        if(SaveThis != "") {
        	vector<string> stringresult;
        	stringresult = parseMessage(SaveThis);
        	for(int i=0; i < stringresult.size(); i+=2) {
        		cout << "Writing to: " << stringresult[i];
        		cout << " with value: " << stringresult[i+1] << endl;
        		dat->writeActuatorData(stringresult[i], stringresult[i+1]);
        	}

        }

     }
}


vector<string> Control::parseMessage(string message)
{
  vector<string> stringlist;
  string result;
  string result2;
  string temp;

  int i;
  for (i=0; i != message.size(); i++)   {

    if (!(message[i] == ';' || message[i] == ':'))
    temp += message[i];

    else {
        stringlist.push_back(temp);
        temp = "";
    }

    }

    if (result[5] == '\0') { cout << "BINGO: " << result[5] << endl;}
	return stringlist;

}


