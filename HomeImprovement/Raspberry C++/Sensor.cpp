#include "Sensor.h"

Sensor::Sensor(string k, string val) : key(k), value(val) {}

Sensor::~Sensor() {}

void Sensor::setValue(string val)
{
    value = val;
}

string Sensor::getValue()
{
    return value;
}

string Sensor::getKey()
{
	return key;
}
