#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H

#include <exception>

class SocketException : public std::exception {
	const char* msg;
	
	public:
	SocketException(const char*);	
	
	const char* what() const noexcept;
};

#endif

