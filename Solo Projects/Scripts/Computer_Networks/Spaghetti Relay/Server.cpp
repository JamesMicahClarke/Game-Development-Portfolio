#include "Server.h"

int Server::init(uint16_t port)
{
	//Create Socket
	serverSocketAddr.listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocketAddr.listenSock == INVALID_SOCKET)
	{
		return SETUP_ERROR;
	}

	//Bind Socket
	serverSocketAddr.in_address.sin_family = AF_INET;
	serverSocketAddr.in_address.sin_addr.S_un.S_addr = INADDR_ANY;
	serverSocketAddr.in_address.sin_port = htons(port);

	serverSocketAddr.tempResult = bind(serverSocketAddr.listenSock, (SOCKADDR*)&serverSocketAddr.in_address, sizeof(serverSocketAddr.in_address));
	if (serverSocketAddr.tempResult == SOCKET_ERROR)
	{
		return BIND_ERROR;
	}

	//Listen
	serverSocketAddr.tempResult = listen(serverSocketAddr.listenSock, 1);
	if (serverSocketAddr.tempResult == SOCKET_ERROR)
	{
		return SETUP_ERROR;
	}

	//Accept Socket Connection
	serverSocketAddr.communSock = accept(serverSocketAddr.listenSock, NULL, NULL);
	if (serverSocketAddr.communSock == INVALID_SOCKET)
	{
		serverSocketAddr.findError = WSAGetLastError();
		if (serverSocketAddr.findError != WSAESHUTDOWN)
		{
			return CONNECT_ERROR;

		}
		if (serverSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}
	}
	return SUCCESS;
}
int Server::readMessage(char* buffer, int32_t size) //size of the gui text bar. Make sure the message can fit!
{

	//Server Communication
	serverSocketAddr.bufSize = 0;
	serverSocketAddr.tempResult = recieveMessage(serverSocketAddr.communSock, (char*)&serverSocketAddr.bufSize, 1);
	if (serverSocketAddr.tempResult == SOCKET_ERROR || serverSocketAddr.tempResult == 0)
	{
		serverSocketAddr.findError = WSAGetLastError();
		if (serverSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;
		}
		else if (serverSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}

	}



	char* b = new char[size];

	serverSocketAddr.tempResult = recieveMessage(serverSocketAddr.communSock, (char*)b, size);
	if (serverSocketAddr.tempResult == SOCKET_ERROR || serverSocketAddr.tempResult == 0)
	{
		serverSocketAddr.findError = WSAGetLastError();
		if (serverSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;
		}
		else if (serverSocketAddr.findError == WSAESHUTDOWN)
		{
			delete[] b;
			return SHUTDOWN;
		}

	}
	delete[] b;
	return SUCCESS;
}
int Server::sendMessage(char* data, int32_t length)
{
	serverSocketAddr.tempResult = Messenger(serverSocketAddr.communSock, (char*)length, 1);
	if (serverSocketAddr.tempResult == SOCKET_ERROR || (serverSocketAddr.tempResult == 0))
	{
		serverSocketAddr.findError = WSAGetLastError();
		if (serverSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;

		}
		if (serverSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}
	}



	char sender[256];
	memset(sender, 0, length);
	strcpy_s(sender, data);

	serverSocketAddr.tempResult = Messenger(serverSocketAddr.communSock, sender, length);
	if (serverSocketAddr.tempResult == SOCKET_ERROR || (serverSocketAddr.tempResult == 0))
	{
		serverSocketAddr.findError = WSAGetLastError();
		if (serverSocketAddr.findError != WSAESHUTDOWN)
		{
			return DISCONNECT;

		}
		if (serverSocketAddr.findError == WSAESHUTDOWN)
		{
			return SHUTDOWN;
		}
	}

	return SUCCESS;
}
void Server::stop()
{
	shutdown(serverSocketAddr.listenSock, SD_BOTH);
	closesocket(serverSocketAddr.listenSock);

	shutdown(serverSocketAddr.communSock, SD_BOTH);
	closesocket(serverSocketAddr.communSock);
}

//Recv func Helper
int Server::recieveMessage(SOCKET socket, char* buffer, int length)
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

//send func Helper
int Server::Messenger(SOCKET socket, const char* data, uint32_t length)
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