#include "Zuil.h"

Zuil::Zuil(char* ip) : Device(ip) {

	a1 = new Actuator("7", "0");
	addActuator("7", a1);
	s1 = new Sensor("8", "0");
	addSensor(s1);
	s1 = new Sensor("9", "0");
	addSensor(s1);

}

Zuil::~Zuil() {

	delete a1;
	delete s1;

}

string Zuil::logic(map<string, Device*> dev)
{
	cout << "This is logic zuil" << endl;
	cout << " " << endl;
}

