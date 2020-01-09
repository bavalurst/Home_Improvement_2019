#include "Control.h"

Control::Control() 
{
    dat = new Database();                     // create new database object

    Device *bed = new Bed("10.42.0.10");           // create new device
    addDevice(bed);                                // add device to map for devices
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
        	vector<string> result;
        	result = parseMessage(buffer);

        	for(int i=0; i < result.size(); i+=2)
        	{

        		  cout << " key: "  << result[i] << " value : " << result[i + 1] << endl;

        	 }

        	if(!((*sens)->getValue() == dat->readData(key)))
        	{
        		(*sens)->
        				setValue(dat->readData(key));
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

  for (i=0; i != sizeof(message); i++)   {


    if (!(message[i] == ';' || message[i] == ':'))
    temp += message[i];

    else {
        stringlist.push_back(temp);
        temp = "";
    }


    }
  /*string stringarray[stringlist.size()];
  int f = 0;

  //cout << stringlist.size();

  std::list<string>::iterator it;
  for(it = stringlist.begin(); it != stringlist.end(); ++it) {

      stringarray[f] = it->c_str();
      f++;
      //cout << it->c_str() << endl;*/



	return stringlist;


}


