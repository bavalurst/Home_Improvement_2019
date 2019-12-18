/*
 * Socket.cpp
 *
 *  Created on: 13 dec. 2019
 *      Author: jordy
 */


#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>

#define PORT 3000

using namespace std;

class Socket
{
private:
    int sock = 0;
    int valread = 0;
    int num = 0;
    char *data = "7";
    char buffer[4] = {0};
public:
    Socket();
    ~Socket();
    int connectToServer(char*);
    void sendMessage();
    void disconnect();
    int receiveMessage();
};

#endif /* SOCKET_H_ */

