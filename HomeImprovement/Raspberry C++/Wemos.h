#ifndef WEMOS_H
#define WEMOS_H

#include <iostream>
#include <map>
#include <list>
#include <string>

#include "Socket.h"

using namespace std;

class Wemos
{
private:
    int value;
    map<int, Wemos*> data;
    char* ip_addr;
    Socket s1;
public:
    Wemos(/* args */);
    Wemos(int, char*);
    ~Wemos();
    map<int, Wemos*> getWemos();
    int getData();
    void sendData(int);
};

#endif /* WEMOS_H */
