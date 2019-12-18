#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <iostream>

using namespace std;

class Actuator
{
private:
	int key;
    int value;
public:
    Actuator(int, int);
    ~Actuator();
    void setValue(int);
    int getValue();
    int getKey();
};

#endif /* ACTUATOR_H */
