#include "Database.h"

Database::Database(/* args */) {}

Database::Database(int val) :  value(val) {}

Database::~Database() {}

map<int, Database*> Database::getDatabase()
{
    int i = 6; // fake data, moet van database komen

    data.clear(); // maak map leeg
   
    data.insert(make_pair(1, new Database(i))); // new Database entry

    return data;
}

int Database::getData()
{
    return value;
}

void Database::sendData()
{

}
