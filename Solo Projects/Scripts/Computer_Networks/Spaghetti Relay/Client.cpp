#include "Client.h"
#include <ws2tcpip.h>

int Client::init(uint16_t port, char* address)
{
	clientSocketAddr.communSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocketAddr.communSock == INVALID_SOCKET)
	{
		return SETUP_ERROR;
	}

	// Add SIN_FAMILY to SOCKADDR_IN struct
	clientSocketAddr.in_address.sin_family = AF_INET;

	// Add user's input IP ADDRESS to SOCKADDR_IN struct
	IN_ADDR sin_addr;
	clientSocketAddr.findError = inet_pton(AF_INET, address, &sin_addr);
	if (clientSocketAddr.findError == SOCKET_ERROR || clientSocketAddr.findError == 0)
	{
		return ADDRESS_ERROR;
	}
	clientSocketAddr.in_address.sin_addr = sin_addr;
	/*
	if (clientSocketAddr.findError == INADDR_NONE)
	{
		return ADDRESS_ERROR;
	}*/

	// Add user's input PORT NUMBER to SOCKADDR_IN struct
	clientSocketAddr.in_address.sin_port = htons(port);

	// Connect with the populated SOCKADDR_IN struct
	clientSocketAddr.tempResult = connect(clientSocketAddr.communSock, (SOCKADDR*)&clientSocketAddr.in_address, sizeof(clientSocketAddr.in_address));
	if (clientSocketAddr.tempResult == SOCKET_ERROR)
	{
		clientSocketAddr.findError = WSAGetLastError();
		if (clientSocketAddr.findError != WSAESHUTDOWN)
		{
			return CONNECT_ERROR;

		}
		if (clientSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;

		}
	}

	return SUCCESS;
}
int Client::readMessage(char* buffer, int32_t size)
{
	clientSocketAddr.tempResult = recieveMessage(clientSocketAddr.communSock, (char*)&size, 1);
	if ((clientSocketAddr.tempResult == SOCKET_ERROR) || (clientSocketAddr.tempResult == 0))
	{
		clientSocketAddr.findError = WSAGetLastError();
		if (clientSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;
		}
		else if (clientSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}

	}
	char* b = new char[size];

	clientSocketAddr.tempResult = recieveMessage(clientSocketAddr.communSock, (char*)b, size);
	if ((clientSocketAddr.tempResult == SOCKET_ERROR) || (clientSocketAddr.tempResult == 0))
	{
		clientSocketAddr.findError = WSAGetLastError();
		if (clientSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;
		}
		else if (clientSocketAddr.findError == WSAESHUTDOWN)
		{
			delete[] b;
			return SHUTDOWN;
		}
	}
	delete[] b;
	return SUCCESS;
}
int Client::sendMessage(char* data, int32_t length)
{
	char sender[256];
	memset(sender, 0, length);
	strcpy_s(sender, data);

	clientSocketAddr.tempResult = Messenger(clientSocketAddr.communSock, (char*)&length, 1);
	if (clientSocketAddr.tempResult == SOCKET_ERROR || (clientSocketAddr.tempResult == 0))
	{
		clientSocketAddr.findError = WSAGetLastError();
		if (clientSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;

		}
		if (clientSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}
	}

	clientSocketAddr.tempResult = Messenger(clientSocketAddr.communSock, sender, length);
	if (clientSocketAddr.tempResult == SOCKET_ERROR || (clientSocketAddr.tempResult == 0))
	{
		clientSocketAddr.findError = WSAGetLastError();
		if (clientSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;

		}
		if (clientSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}
	}

	return SUCCESS;
}
void Client::stop()
{
	shutdown(clientSocketAddr.communSock, SD_BOTH);
	closesocket(clientSocketAddr.communSock);

	shutdown(clientSocketAddr.communSock, SD_BOTH);
	closesocket(clientSocketAddr.communSock);
}
int Client::recieveMessage(SOCKET socket, char* buffer, int length)
{
	int total = 0;
	do
	{
		int check = recv(socket, buffer + total, length - total, 0);
		if (check > length)
		{
			return PARAMETER_ERROR;
		}
		if (check < 1)
		{
			return check;
		}
		else
			total += check;

	} while (total < length);


	return total;
}
int Client::Messenger(SOCKET socket, const char* data, uint32_t length)
{
	int res;
	int sendLength = 0;

	while (sendLength < length)
	{
		res = send(socket, (const char*)data + sendLength, length - sendLength, 0);
		if (res <= 0 || res > 255)
		{
			return PARAMETER_ERROR;
		}
		else
			sendLength += res;
	}
	return sendLength;
}