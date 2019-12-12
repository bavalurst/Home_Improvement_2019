#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Database
{
private:
    int value;
    map<int, Database*> data;
public:
    Database(/* args */);
    Database(int);
    ~Database();
    map<int, Database*> getDatabase();
    int getData();
    void sendData();
};


#endif /* DATABASE_H */
