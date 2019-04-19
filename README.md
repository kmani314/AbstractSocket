# AbstractSocket
AbstractSocket is an easy to use way to interface with TCP Sockets with modern exception handling (no more errno).

### Server Example:
```c++
try {
	AbstractSocket mySocket(); 

	mySocket.listen(8080, 10); // Attach to port 8080 with a max connection queue of 10

	mySocket.waitForConnection(); // Blocks until incoming connection

	char* msg = "Hello World!";
	mySocket.write(msg, strlen(msg)); // Sending to the socket is as easy as that

} catch(std::exception& e) { // AbstractSocket comes with SocketException, which inherits from std::exception
	std::cout << e.what() << std::endl;
}
```
### Client Example:
```c++
try {
	AbstractSocket mySocket();
	
	mySocket.connect(8080, "127.0.0.1"); // Connect to 127.0.0.1 on port 8080
	char buf[256] = {0};
	mySocket.read(buf, 256); // Read 256 bytes into buf

	std::cout << buf << std::endl;
} catch(std::exception& e) {
	std::cout << e.what() << std::endl;
}
```
