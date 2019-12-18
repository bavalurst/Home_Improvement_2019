/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */

#ifndef DATABASE_H
#define DATABASE_H

#include "Control.h"
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <string>

#include "json.h"
#include "reader.h"

using namespace Json;
using namespace std;

class Database
{
private:
    int value = 0;
    stringstream buffer; //Temporary string buffer for reading JSON
    Reader reader; //Needed to read and parse a string to json.
    Value data; //JSON object, where logic can be applied.
    StyledStreamWriter writer; //Writes JSON data to file
public:
    Database();
    ~Database();
    int receiveMessage();
    void setValue(int);
    int getValue();
    int getKey();
    void updateData(string, string);
    void refreshData();
    string readData(string);
};


#endif /* DATABASE_H */
