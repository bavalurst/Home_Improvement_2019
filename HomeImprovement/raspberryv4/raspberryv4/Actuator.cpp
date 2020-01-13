#include "Actuator.h"

Actuator::Actuator(string k, string val) : key(k), value(val) {}


Actuator::~Actuator() {}

void Actuator::setValue(string val)
{
    value = val;
}

string Actuator::getValue()
{
    return value;
}

string Actuator::getKey()
{
	return key;
}
