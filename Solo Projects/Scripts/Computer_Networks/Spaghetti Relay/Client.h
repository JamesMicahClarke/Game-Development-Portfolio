#pragma once
#include "../platform.h"
#include "../definitions.h"

 
class Client
{
private:
	struct socketAddress
	{
		SOCKET communSock; //Communication socket
		sockaddr_in in_address;
		uint8_t bufSize;
		int tempResult;
		int findError;
	};

public:

	socketAddress clientSocketAddr;


	int init(uint16_t port, char* address);
	int readMessage(char* buffer, int32_t size);
	int sendMessage(char* data, int32_t length);
	int recieveMessage(SOCKET socket, char* buffer, int length);
	int Messenger(SOCKET socket, const char* data, uint32_t length);
	void stop();
};