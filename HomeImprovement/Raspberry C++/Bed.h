/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#ifndef BED_H
#define BED_H

#include "Device.h"

class Socket;

class Bed : public Device
{
private:
    /* data */
public:
    Bed(int, char*, Socket*);
    virtual ~Bed();
    virtual void logic();
};

#endif /* BED_H */
