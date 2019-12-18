#ifndef DATABASE_H
#define DATABASE_H

#include <unistd.h>
#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <streambuf>
#include <string>

//#include "json.h"
//#include "reader.h"

//using namespace Json;
using namespace std;

class Database
{
private:
    //stringstream buffer; //Temporary string buffer for reading JSON
    //Reader reader; //Needed to read and parse a string to json.
    //Value data; //JSON object, where logic can be applied.
    //StyledStreamWriter writer; //Writes JSON data to file
public:
    Database();
    ~Database();
    int receiveMessage();
    void updateData(string, string);
    void refreshData();
    int readData(int);
};


#endif /* DATABASE_H */
