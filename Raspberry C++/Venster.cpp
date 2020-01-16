#include "Venster.h"

Venster::Venster(char* ip) : Device(ip) {

	a1 = new Actuator("14", "0");	// ledstrip		waarde 0 tot 10
	addActuator("14", a1);
	a2 = new Actuator("15", "0");	// window 		waarde 1 of 0
	addActuator("15", a2);
	s1 = new Sensor("16", "0");		// dimmer
	addSensor(s1);
	s2 = new Sensor("17", "0");		// LDR			onder 400 uit
	addSensor(s2);

}

Venster::~Venster() {

	delete a1;
	delete a2;
	delete s1;
	delete s2;

}

string Venster::logic(map<string, Device*> dev)
{
	string s = "";
	if(stoi(this->s2->getValue()) <= 400){
		s = s + "15;1;";
		cout << "turning window on" << endl;
	}
	else{
		s = s + "15;0;";
	}

	string LedValue = (this->s1->getValue());
	s = s + "14;" + LedValue + ";";


	return s;
}

