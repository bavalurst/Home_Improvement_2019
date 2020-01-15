#include "Stoel.h"

Stoel::Stoel(char* ip) : Device(ip) {

	a1 = new Actuator("4", "0");
	addActuator("4", a1);
	a1 = new Actuator("5", "0");
	addActuator("5", a1);
	s1 = new Sensor("6", "0");
	addSensor(s1);
	s1 = new Sensor("7", "0");
	addSensor(s1);

}

Stoel::~Stoel() {

	delete a1;
	delete s1;

}

string Stoel::logic(map<string, Device*> dev)
{
	cout << "This is logic stoel" << endl;
	cout << " " << endl;
}

