#include "Device.h"

Device::Device(char* ip) : ip_addr(ip) {}

Device::~Device() {}

char* Device::getIP()
{
	return ip_addr;
}

int Device::sendMessage(string str)
{
	data = str.c_str();

	struct sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		sock = 0;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	send(sock , data, strlen(data) , 0 );

	usleep(50000);

	close(sock);

	shutdown(sock, SHUT_RDWR);
}

string Device::receiveMessage()
{
	int i;
	for(i = 0; i < 25; i ++)
		buffer[i] = '\0';
	struct sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		usleep(1000000);
		//return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		//return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		//return -1;
	}

	valread = read( sock , buffer, 128);

	usleep(50000);

	shutdown(sock, SHUT_RDWR);

	cout << "Recieved message: " << buffer << endl;

	string appel = buffer;

	close(sock);

	return appel;
}

string Device::logic(map<string, Device*> dev)
{

	return "0";
}

void Device::addActuator(string key, Actuator* a)
{
	actuatorId.insert(make_pair(key, a));
}

void Device::addSensor(Sensor* s){

	sensorId.insert(make_pair(s->getKey(), s));
}

map<string, Sensor*> Device::getSensors(){

	return sensorId;

}

map<string, Actuator*> Device::getActuators()
{
	return actuatorId;
}


