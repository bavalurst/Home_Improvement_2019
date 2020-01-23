#include "Control.h"

Control::Control() 
{
    dat = new Database();                     // create new database object
    Device *bed = new Bed("10.42.0.10");           // create new device
    addDevice("Bed", bed); // create bed

    Device *stoel = new Stoel("10.42.0.14");
    addDevice("Stoel", stoel);// add device to map for devices

    Device *zuil = new Zuil("10.42.0.16");
    addDevice("Zuil", zuil); // add zuil

    Device *schemerlamp = new Schemerlamp("10.42.0.13");
    addDevice("Schemerlamp", schemerlamp); // add schemerlamp

    Device *fridge = new Fridge("10.42.0.12");
    addDevice("Fridge", fridge); // add fridge

    Device *deur = new Deur("10.42.0.11");
    addDevice("Deur", deur); // add Deur

    Device *venster = new Venster("10.42.0.15");
    addDevice("Venster", venster); // add Venster


}       

Control::~Control()
{
    delete dat;
}

void Control::addDevice(string key, Device* d1)
{
    devices.insert(make_pair(key, d1)); //Adds device to map
}


void Control::compareDatabaseToDevice()
{   
    // compare the values from the map with databases and the map from devices with each other, and act accordingly
    for (map<string, Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev)
    {
        map<string, Actuator*> a1 = dev->second->getActuators(); //gets a map of actuators from device located at iterator from device map
        map<string, Sensor*> sensors;                            //initialize sensormap and iterator
        map<string, Sensor*>::iterator it;
        sensors = dev->second->getSensors();

        for(map<string, Actuator*>::iterator act = a1.begin(); act != a1.end(); ++act) //for each actuator in device..
        {
            string key = act->first; //get the key of the actuator, used to get the right values from actuator.json

            if(!(act->second->getValue() == dat->readActuatorData(key))) //if the value in actuator.json is not equal to the value inside actuator object.
		    							//the actuator value will be equal to the actuator.json, and the value will be sent to the device. 
            {
            	//cout << "Sending: " << dat->readActuatorData(key) << "To Key: " << key << endl;
            	act->second->setValue(dat->readActuatorData(key));
                dev->second->sendMessage(act->second->getKey() + dat->readActuatorData(key));
            }
        }
        medicine(); //initialize medicine check
        usleep(100000); // wait 100ms to prevent socket failure

        string buffer = dev->second->receiveMessage(); //new string is equal to receive message from device in loop
        vector<string> result; //initialize vector
        result = parseMessage(buffer); //convert the received message into a vector<string> with parsed key values (see parseMessage Comments for more info)

        for(int i=0; i < result.size(); i+=2) //for each entry in the vector
        	{
        		it = sensors.find(result[i]); //find the sensorlocation in map with the key found in the result vector.

        		if(it != sensors.end()) { //for that sensor, set the value of the sensor equal to the value recieved earlier, and store it in the sensor.json file
        			it->second->setValue(result[i + 1]);
        			dat->updateSensorData(result[i], result[i + 1]);
        			cout << "Updating with key: " << result[i] << " Value: " << result[i+1] << endl; 
        		}
            }

        string SaveThis = dev->second->logic(devices); //execute logic from device, returns an empty string if nothing should be done. Returns a key/value string (to be parsed) if actuator values should change.
        if(SaveThis != "") {
        	vector<string> stringresult;
        	stringresult = parseMessage(SaveThis);
        	for(int i=0; i < stringresult.size(); i+=2) {
        		/*cout << "Writing to: " << stringresult[i];
        		cout << " with value: " << stringresult[i+1] << endl;*/
			dat->createLog("Writing to: " + stringresult[i] + " with value: " + stringresult[i + 1] + "\n"); //create log
        		dat->writeActuatorData(stringresult[i], stringresult[i+1]); //To change actuator values, they will be written in the database. The next loop will catch it, and send the proper message.
        	}

        }

     }
}


vector<string> Control::parseMessage(string message) //parses messages recieved by wemos or commands by this code and returns them in a vector<string>
{
  vector<string> stringlist; //initialize empty vector
  string result;
  string result2;
  string temp;

  int i;
  for (i=0; i != message.size(); i++)   { //loop through each character in a string

    if (!(message[i] == ';' || message[i] == ':')) //for each character which is not a ':' or a ';'
    temp += message[i]; //add this character to a temporary string

    else { //if the loop hit a ':' or ';'
        stringlist.push_back(temp); //add the temporary string to the vector
        temp = ""; //and empty the temporary, for repetitions
    }

    }

    //if (result[5] == '\0') { cout << "BINGO: " << result[5] << endl;}
    return stringlist;

}

void Control::medicine() {
	//cout << Time << endl;
	if ((time(nullptr) - Time) >= 60) { 
		//cout << endl << endl << endl << "Medicijnen innemen!" << endl << endl << endl;
		dat->writeActuatorData("35", "1");
		Time = time(nullptr);
		medicIntakeTime = time(nullptr);
		}
	if (((time(nullptr) - medicIntakeTime) >= 10)  && (dat->readActuatorData("35") == "1") && (dat->readActuatorData("36") == "0")) {
		//cout << endl << endl << endl << "Timmothy heeft zijn medicijnen niet ingenomen !!!!!!!!!!!!!!111" << endl << endl << endl;
		dat->writeActuatorData("36", "1");
		dat->writeActuatorData("35", "0");
		medicIntakeTime = time(nullptr);
	}
}

