/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Device.h"

Device::Device(char* ip, Socket* s) : ip_addr(ip), s1(s) {}

Device::~Device() {}

char* Device::getIP()
{
	return ip_addr;
}

void Device::setValue(int val)
{
	value = val;
}

int Device::getValue()
{
	return value;
}

Socket* Device::getSocket()
{
	return s1;
}

void Device::logic()
{
	cout << "This is logic device" << endl;
}


