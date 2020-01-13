#include "Bed.h" 

Bed::Bed(char* ip) : Device(ip) 
{
	a1 = new Actuator("1", "0");
	addActuator(a1);
	s1 = new Sensor("2", "0");
	addSensor(s1);
	s1 = new Sensor("3", "0");
	addSensor(s1);
}

Bed::~Bed() {}

void Bed::logic()
{
	cout << " " << endl;
	cout << "This is logic bed" << endl;
}


