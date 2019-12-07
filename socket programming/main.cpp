/*
 * main.cpp
 *
 *  Created on: 7 dec. 2019
 *      Author: jordy
 */

#include "Socket.h"

int main()
{
	Socket wemos("10.42.0.123");

	wemos.connectToClient();
	wemos.sendMessage();
	wemos.receiveMessage();
}



