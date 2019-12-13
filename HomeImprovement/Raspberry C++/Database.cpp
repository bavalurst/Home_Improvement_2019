/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#include "Database.h"

Database::Database() {}

Database::~Database() {}

int Database::receiveMessage()
{
    return 6;
}

void Database::setValue(int val)
{
    value = val;
}

int Database::getValue()
{
    return value;
}
