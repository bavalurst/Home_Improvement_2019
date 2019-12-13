/*
 * Stoel.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Stoel.h"

Stoel::Stoel(char* ip, Socket* s) : Device(ip, s) {}

Stoel::~Stoel() {}

void Stoel::logic()
{
	cout << "This is logic stoel" << endl;
	cout << " " << endl;
}

