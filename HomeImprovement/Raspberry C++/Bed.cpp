/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Bed.h" 

Bed::Bed(int i, char* ip, Socket* s) : Device(i, ip, s)
{
	
}

Bed::~Bed() {}

void Bed::logic()
{
	cout << "This is logic bed" << endl;
}

