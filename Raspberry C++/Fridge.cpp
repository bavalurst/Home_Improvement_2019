#include "Fridge.h"

Fridge::Fridge(char* ip) : Device(ip) {
	timeStart = time(nullptr);
	a1 = new Actuator("18", "0");	// cooling+fan -> send 1
	addActuator("18", a1);
	s1 = new Sensor("19", "0");		// temp inside  || 0 - 1023
	addSensor(s1);
	s2 = new Sensor("21", "0");		// doorsensor	|| 0 - 1
	addSensor(s2);

}

Fridge::~Fridge() {

	delete a1;
	delete s1;
	delete s2;

}

string Fridge::logic(map<string, Device*> dev)
{
	string s = "";

	if(stoi(this->s1->getValue()) > 300 && stoi(this->s2->getValue()) == 1){
		s = s + "18;1;";
		cout << "fridge on" << endl;
		deurOpen = 0;
		cout << deurOpen << endl;
	}

	if(stoi(this->s2->getValue()) ==  0 && deurOpen == 0){
		timeStart = time(nullptr);
		cout << "huidige tijd" << timeStart << endl;
		deurOpen = 1;
	}

	if(time(nullptr) >= (timeStart + 10) && deurOpen == 1){
		s = s + "18;0;";
		cout << "fridge off" << endl;
	}

	return s;
}


