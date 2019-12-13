/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Database
{
private:
    int value = 0;
public:
    Database();
    ~Database();
    int receiveMessage();
    void setValue(int);
    int getValue();
    int getKey();
};


#endif /* DATABASE_H */