#ifndef DATABASE_H
#define DATABASE_H

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <string>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>

using namespace Json;
using namespace std;

class Database
{
private:
    stringstream buffer; //Temporary string buffer for reading JSON
    Reader reader; //Needed to read and parse a string to json.
    Value sensor; //JSON object, where logic can be applied.
    Value actuator;
    StyledStreamWriter writer; //Writes JSON data to file
    stringstream stringtime;

public:
    Database();
    ~Database();
    void updateSensorData(string, string);
    void refreshSensorData();
    void refreshActuatorData();
    string readActuatorData(string);
    void writeActuatorData(string, string);
    void createLog(string);
};


#endif /* DATABASE_H */
