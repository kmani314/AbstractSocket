#ifndef ABSTRACT_SOCKET_H
#define ABSTRACT_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/types.h>
#include "unistd.h"

typedef struct sockaddr_in sockaddr_in;

class AbstractSocket {
	private:
	int descriptor;
	int connectedSocket = -1;

	int socketOption;
	
	sockaddr_in address;
	
	public:
	AbstractSocket(int);

	void listen(int, int);
	void connect(int, const char*);
	
	void waitForConnection();

	int write(const void*, int);
	int read(void*, int);
};

#endif
