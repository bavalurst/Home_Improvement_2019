#ifndef SENSOR_H_
#define SENSOR_H_

#include <iostream>

using namespace std;

class Sensor {
private:
	string key;
    string value = 0;
public:
	Sensor(string, string);
	virtual ~Sensor();
    void setValue(string);
    string getValue();
    string getKey();
};

#endif /* SENSOR_H_ */
