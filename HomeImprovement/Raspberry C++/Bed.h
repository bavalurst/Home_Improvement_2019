#ifndef BED_H
#define BED_H

#include "Device.h"

class Bed : public Device
{
private:
    
public:
    Bed(char*);
    virtual ~Bed();
    virtual void logic();
};

#endif /* BED_H */
