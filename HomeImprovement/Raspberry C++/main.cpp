/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Control.h"

int main()
{
    Control c1; // create control class

    while(1)
    {
    	usleep(50000);						// wait 50ms
    	c1.compareDatabaseToDevice();		// compare data from Database to Devices
    }
}
