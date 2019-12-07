/*
 * Socket.cpp
 *
 *  Created on: 7 dec. 2019
 *      Author: jordy
 */

#include "Socket.h"

Socket::Socket(char *ip) : ip_addr(ip) {}

Socket::~Socket() {}

int Socket::connectToClient()
{
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
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
}

void Socket::sendMessage()
{
    send(sock , hello, strlen(hello) , 0 );
	printf("Hello message sent\n");
}

void Socket::receiveMessage()
{
    while(1)
	{
		valread = read( sock , buffer, 4);

		for(int i = 0; i < valread; i++)
		{
			cout << buffer[i];
		}

		cout << " " << endl;
	}
}





