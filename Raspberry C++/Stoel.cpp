#include "Stoel.h"

Stoel::Stoel(char* ip) : Device(ip) {

	a1 = new Actuator("4", "0");
	addActuator(a1);
	s1 = new Sensor("5", "0");
	addSensor(s1);
	s1 = new Sensor("6", "0");
	addSensor(s1);

}

Stoel::~Stoel() {

	delete a1;
	delete s1;

}

void Stoel::logic()
{
	cout << "This is logic stoel" << endl;
	cout << " " << endl;
}

