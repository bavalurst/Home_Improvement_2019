#include "Schemerlamp.h"

Schemerlamp::Schemerlamp(char* ip) : Device(ip) {

	a1 = new Actuator("10", "0");
	addActuator("10", a1);
	s1 = new Sensor("11", "0");
	addSensor(s1);
	s1 = new Sensor("12", "0");
	addSensor(s1);

}

Schemerlamp::~Schemerlamp() {

	delete a1;
	delete s1;

}

string Schemerlamp::logic(map<string, Device*> dev)
{
	cout << "This is logic schemerlamp" << endl;
	cout << " " << endl;
}

