#include "Actuator.h"

Actuator::Actuator(int k, int val) : key(k), value(val) {}


Actuator::~Actuator() {}

void Actuator::setValue(int val)
{
    value = val;
}

int Actuator::getValue()
{
    return value;
}

int Actuator::getKey()
{
	return key;
}
