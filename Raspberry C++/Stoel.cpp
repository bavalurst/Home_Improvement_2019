#include "Stoel.h"

Stoel::Stoel(char* ip) : Device(ip) {

	timeStart = time(nullptr);
	alarm = NULL;
	cooldown = NULL;
	oneSecond = timeStart + 1;
	a1 = new Actuator("4", "0"); //Actuator voor trillfunctie
	addActuator("4", a1);
	a2 = new Actuator("5", "0"); //Actuator voor LED
	addActuator("5", a1);
	s1 = new Sensor("6", "0"); //sensor voor druksensor
	addSensor(s1);
	s2 = new Sensor("7", "0"); //sensor voor stoelknop
	addSensor(s2);

}

Stoel::~Stoel() {

	delete a1;
	delete s1;
	delete s2;

}

string Stoel::logic(map<string, Device*> dev)
{
	string s = "";

	timeStart = time(nullptr);

	//massage function
	if(s1->getValue() == "1" && alarm == NULL && cooldown == NULL) {
		s = "4;1;5;1;33;1;";
		alarm = timeStart + 5;
		cout << "Massage initiated \n";
	}

	if(timeStart > alarm && alarm != NULL){ //trill functie beindigen na 5 seconden
		alarm = NULL;
		s = "4;0;5;0;33;0;";
		cooldown = timeStart + 5;
		cout << "Massage ended \n";
	}

	if(timeStart > cooldown && cooldown !=NULL){ //5 seconden cooldown voor massage functie
		cooldown = NULL;
		cout << "Massage cooldown ended \n";
	}

	//seisure detection
	if(seizureTime == 0){
		previousPressure = stoi(this->s1->getValue());
		seizureTime++;
	}

	if(seizureTime >= 1){
		previousPressure = stoi(this->s1->getValue());
		//
		currentPressure = stoi(this->s1->getValue());
		if((currentPressure - previousPressure > 200 || currentPressure - previousPressure > -200) && seizureTime < 3){
			seizureLevel++;
			previousPressure = currentPressure;
		}
		else{
			seizureLevel = 0;
			seizureTime = 0;
		}

		if(seizureLevel == 3 && seizureTime >= 3){
			s = s + "33;1;";
			cout << "Seizure Detected";
		}
	}
	//cout << "This is logic stoel" << endl;
	//cout << " " << endl;

	return s;
}
