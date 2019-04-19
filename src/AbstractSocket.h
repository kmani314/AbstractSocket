#ifndef ABSTRACT_SOCKET_H
#define ABSTRACT_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/types.h>
#include "unistd.h"
#include <string>

typedef struct sockaddr_in sockaddr_in;

class AbstractSocket {
	private:
	int descriptor;
	int connectedSocket = -1;

	int socketOption = 1;
	
	sockaddr_in address;
	
	public:
	AbstractSocket();

	void listen(int, int);
	void connect(int, std::string);
	
	void waitForConnection();

	int write(const void*, int);
	int read(void*, int);
};

#endif
