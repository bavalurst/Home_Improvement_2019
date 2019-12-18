#include "Bed.h" 

Bed::Bed(char* ip) : Device(ip) {}

Bed::~Bed() {}


void Bed::logic()
{
	cout << " " << endl;
	cout << "This is logic bed" << endl;
}


