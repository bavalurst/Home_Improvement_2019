#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <iostream>

using namespace std;

class Actuator
{
private:
	string key;
    string value = 0;
public:
    Actuator(string, string);
    ~Actuator();
    void setValue(string);
    string getValue();
    string getKey();
};

#endif /* ACTUATOR_H */
