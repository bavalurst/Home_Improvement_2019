#include "Schemerlamp.h"

Schemerlamp::Schemerlamp(char* ip) : Device(ip) {

	a1 = new Actuator("10", "0");
	addActuator(a1);
	s1 = new Sensor("11", "0");
	addSensor(s1);
	s1 = new Sensor("12", "0");
	addSensor(s1);

}

Schemerlamp::~Schemerlamp() {

	delete a1;
	delete s1;

}

void Schemerlamp::logic()
{
	cout << "This is logic schemerlamp" << endl;
	cout << " " << endl;
}

