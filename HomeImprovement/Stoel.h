#ifndef STOEL_H
#define STOEL_H

#include "Device.h"

class Stoel : public Device
{
private:
    /* data */
public:
    Stoel(char*);
    virtual ~Stoel();
    virtual void logic();
};

#endif /* STOEL_H */
