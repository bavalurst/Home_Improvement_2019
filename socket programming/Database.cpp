#include <iostream>
#include <map>

using namespace std;

class Database
{
private:
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    map<int, int> data;
    
public:
    Database(/* args */);
    ~Database();
    void receiveData();
    void checkChange();
};

Database::Database(/* args */) {}

Database::~Database() {}

void Database::receiveData()
{
    data.insert(1, value1);
    data.insert(2, value2);
    data.insert(3, value3);


}

int main()
{
    Database d1;
    d1.receiveData();
}
