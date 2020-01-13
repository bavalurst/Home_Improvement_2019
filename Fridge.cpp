#include "Fridge.h"

Fridge::Fridge(char* ip) : Device(ip) {

	a1 = new Actuator("13", "0");
	addActuator(a1);
	s1 = new Sensor("14", "0");
	addSensor(s1);
	s1 = new Sensor("15", "0");
	addSensor(s1);

}

Fridge::~Fridge() {

	delete a1;
	delete s1;

}

void Fridge::logic()
{
	cout << "This is logic Fridge" << endl;
	cout << " " << endl;
}

