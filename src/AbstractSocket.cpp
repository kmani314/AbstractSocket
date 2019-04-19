#include "AbstractSocket.h"
#include "SocketException.h"

AbstractSocket::AbstractSocket() {
	descriptor = socket(AF_INET, SOCK_STREAM, 0); // TCP socket using IPv4

	if(descriptor < 0) throw SocketException("Socket could not be created!"); // Some socket creation error

	if(setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, &socketOption, sizeof(socketOption)) < 0) throw SocketException("Could not set socket option"); // set socket options
	memset(&address, '0', sizeof(address)); 
}

void AbstractSocket::listen(int portNumber, int maxQueue) { // listen on port
	memset(&address, '0', sizeof(address));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(portNumber);

	if(bind(descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) throw SocketException("Socket could not bind");
	
	if(::listen(descriptor, maxQueue) < 0) throw SocketException("Socket could not listen.");
}

void AbstractSocket::connect(int portNumber, std::string hostAddr) { // connect to remote host
	memset(&address, '0', sizeof(address));
	
	address.sin_family = AF_INET;
	address.sin_port = htons(portNumber); // network order

	if(inet_pton(AF_INET, hostAddr.c_str(), &address.sin_addr) <= 0) throw SocketException("Connection Address Invalid.");

	if(::connect(descriptor, (struct sockaddr*)&address, sizeof(address)) < 0) throw SocketException("Failed to connect.");

}

void AbstractSocket::waitForConnection() { // block until incoming request - sets connectedSocket for reading and writing
	int addrlen = sizeof(address);
	connectedSocket = accept(descriptor, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	
	if(connectedSocket < 0) throw SocketException("Could not accept a valid socket.");	
}

int AbstractSocket::write(const void* buf, int len) { // write len bytes from buf to socket
	int sent;
	
	if((sent = send(descriptor, buf, len, 0)) < 0) throw SocketException("Failed to send.");
	return sent; // return number of bytes sent
}

int AbstractSocket::read(void* buf, int len) { // read len bytes from socket into buf
	int read;

	if((read = ::read(connectedSocket, buf, len)) <= 0) throw SocketException("Could not read len bytes from descriptor.");
	
	return read; // return number of bytes read
}
