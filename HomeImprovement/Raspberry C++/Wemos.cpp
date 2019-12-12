#include "Wemos.h"
#include "Socket.h"

Wemos::Wemos(/* args */)
{

}

Wemos::Wemos(int val, char* ip) :  value(val), ip_addr(ip) {}

Wemos::~Wemos() {}

map<int, Wemos*> Wemos::getWemos()
{
    int i = 5; // fake data

    data.clear(); // maak map leeg

    data.insert(make_pair(1, new Wemos(i,"10.42.0.123"))); // new device

    return data;
}

int Wemos::getData()
{
    return value;
}

void Wemos::sendData(int device)
{
	map<int, Wemos*>::iterator it = data.find(device);

	s1.setIP(it->second->ip_addr);
	s1.connectToServer();
	s1.sendMessage();
	s1.receiveMessage();
	s1.disconnect();
}

