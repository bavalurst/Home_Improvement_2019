/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#ifndef STOEL_H
#define STOEL_H

#include "Device.h"

class Socket;

class Stoel : public Device
{
private:
    /* data */
public:
    Stoel(char*, Socket*, string);
    virtual ~Stoel();
    virtual void logic();
};

#endif /* STOEL_H */
