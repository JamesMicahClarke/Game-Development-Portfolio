#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <winsock2.h>
#include <iostream>
#include <ws2tcpip.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")


using namespace std;



class Clients
{
private:

	//holds all variables needed for Client access
	struct Client
	{
		SOCKET tcpSocket;
		SOCKET udpSocket;
		sockaddr_in sockIn;
		IN_ADDR inAddr;
		char* userID[4];
		char command[27];
		int bufsize = 0;
	};

	//sends the entire message to the Server
	int FullSend(SOCKET& comSocket, char* data, uint16_t length);

public:
	//variable used to access all Client variables
	Client cBase;
	//Controls the ClientRun loop
	bool isactive = true;
	//Prevents connection from happening more than once per run
	bool isConnected = true;
	//checks if message is ready to be recieved
	bool ready = false;

	//Initializes sockets
	SOCKET TCPSocketInit(SOCKET sock);
	SOCKET UDPSocketInit(SOCKET sock);
	//Connects Sockets to Server
	void SocketConnect(Clients& clientele, char* address, int port);
	//prompts user for a username that is 15 characters long
	void UsernameIn(Client& clientele, char* username);
	//prompts for a command to register or exit
	void CommandIn(Client& clientele,char* username);
	//sends message to Server
	void Sender(SOCKET& comSocket, char* data, uint16_t length, bool isSent);


};