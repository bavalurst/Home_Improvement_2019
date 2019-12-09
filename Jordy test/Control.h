#ifndef CONTROL_H
#define CONTROL_H

#include "Database.h"
#include "Wemos.h"

class Control
{
private:
    Database d1;
    Wemos w1;
public:
    Control(/* args */);
    ~Control();
    void compareData();
};

#endif /* CONTROL_H */
