/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Bed.h" 

Bed::Bed(char* ip, Socket* s) : Device(ip, s)
{
	
}

Bed::~Bed() {}

void Bed::logic()
{
	cout << " " << endl;
	cout << "This is logic bed" << endl;
}

