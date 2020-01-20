#include "Schemerlamp.h"

Schemerlamp::Schemerlamp(char* ip) : Device(ip) { //This class contains schemerlamp logic, and is able to communicate to the corresponding device

	a1 = new Actuator("8", "0"); 	//The actuator controls the lamp
	addActuator("8", a1);    	//Adds the actuator to the map of actuators this class contains. This class only has 1 actuator.
	s1 = new Sensor("9", "0"); 	//The sensor reads motion
	addSensor(s1);			//Idem line 6
	CurrentTime = time(nullptr); 	//Used to display the current time. Set on object creation and in each loop
	AlarmTime = NULL;		//Used to set an alarm. If this alarm equals the current time, logic occurs.
	fluctuations = 0;              //Used to count the amount of times the sensor sees differentiating motions.

}

Schemerlamp::~Schemerlamp() {

	delete a1;
	delete s1;

}

string Schemerlamp::logic(map<string, Device*> dev) 		//This function is called in each program loop, and accepts a map of devices it can access to get information.
{
    CurrentTime = time(nullptr); 				//resets the CurrentTime value to the current time.
    string s = "";              				//this class returns a string with commands, which sets actuator values. If nothing is to be done, this value remains empty.

    //cout << "Ik heb binnen: " << s1-> getValue() << endl;

	if (s1->getValue() != "0" && AlarmTime == NULL) { 	//if sensor is triggered and alarm is not set
		AlarmTime = (CurrentTime + 10); 		//set an alarm which is the current time plus 10 seconds, and reset the fluctuation count
		fluctuations = 0;				//Just to be sure, clears the fluctuations before counting
	}

	else if (CurrentTime < AlarmTime) { 			//if sensor is triggered, and alarm is running,
		int res = stoi(s1->getValue()); 		//add the sensorvalue to result, and put it in a list. 
		//cout << "Alarm aan: pushing back: " << res << endl;
		AlarmReading.push_back(res);
	}

	else if (CurrentTime > AlarmTime && AlarmTime != NULL){ 	//if the alarm goes off (and is set to do things)
		//cout << "printing alarm reading: " << endl;
		for (int i = 0; i < AlarmReading.size(); i++) { 	//loop through the list of all the values captured during these 10 seconds
				//cout << AlarmReading[i];

			if (i < (AlarmReading.size() - 1)) 		//skip the next line if at the end of the array
			if (AlarmReading[i] != AlarmReading[i + 1]) { 	//if the array contains a value that is unqual to the next value (1 to 0 or 0 to 1)
				fluctuations++; //count a fluctuation
				//cout << "Fluctuatie gevondenop positie: " << i << " Met waarde: " << fluctuations << endl;
				//cout << "Want: " << AlarmReading[i] << "not same as " << AlarmReading[i + 1] << endl;
			}
		}
		
		if (fluctuations >= 3) { 			//if at any point in this loop fluctuations is 3 or higher,
			//cout << "Alarm aan! Meneer sterft." << endl;
			s = s + "31;1;"; 			//send an alarm
		}
		AlarmTime = NULL; 					//after the alarm has gone off, or not, reset the alarm to empty,
		AlarmReading.clear(); 					//clear the vector with readings,
		fluctuations = 0;					//and clean the fluctuations.
	}		
	return s; 							//returns the value to be given to actuators, if needed.
}








