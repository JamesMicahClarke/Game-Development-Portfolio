#pragma once
#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS  

class Servers
{
private:

	//holds all variables needed for Server access
	struct Server
	{
		SOCKET listener, comSocket;
		SOCKET udpSocket;
		SOCKADDR_IN addrIn;
		fd_set masterSet, readySet;
		timeval timeout;

		int registered = 0;
		char userID[15];

		char* userlist[4];
		int listCount = 0;

		int bufsize = 0;
		std::string serverMessage;

	};

	//Initializes Master and Ready sets
	void SetInit(Servers& serv);
	//recvs the entire message sent by client
	int FullRecieve(SOCKET& s, char* buf, int len);

public:
	//variable used to access all Client variables
	Server sBase;
	//bool to control the ServerRun loop
	bool isactive = true;
	//bool to prevent connection from happening more than once per run
	bool isConnected = true;
	bool isRead = true;

	//Initializes sockets
	SOCKET TCPSocketInit(SOCKET sock);
	SOCKET UDPSocketInit(SOCKET sock);
	//Binds sockets
	void SocketBind(Servers& serv, int port);
	//Sets sockets to listen mode
	void SocketListen(Servers& serv, int connections);
	//selects ready sockets
	void Selection(Servers& serv);
	//Accepts connections
	void AcceptConnect(Servers& serv);
	//reads message sent by client
	void Read(Servers& serv, char* message, int size);

};

