/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Device.h"

Device::Device(char* ip, Socket* s, string k) : ip_addr(ip), s1(s), key(k) {}

Device::~Device() {}

char* Device::getIP()
{
	return ip_addr;
}

void Device::setValue(int val)
{
	value = val;
}

string Device::getKey() {

	return key;
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


