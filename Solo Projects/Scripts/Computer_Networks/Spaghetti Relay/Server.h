#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS  
#include "../platform.h"
#include "../definitions.h"

class Server
{
private:
	struct socketAddress
	{
		SOCKET listenSock; //listener socket
		SOCKET communSock; //Communication socket
		sockaddr_in in_address;
		uint32_t bufSize;
		int tempResult;
		int findError;
	};

public:

	socketAddress serverSocketAddr;

	int init(uint16_t port);
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	int recieveMessage(SOCKET socket, char* buffer, int length); //Recv Helper
	int Messenger(SOCKET socket, const char* data, uint32_t length); //send func helper
	void stop();

};