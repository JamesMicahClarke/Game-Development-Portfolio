// Networking Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include "Client.h"
#include "Server.h"

using namespace std;

void ServerRun(Servers& serv, int port, bool& brod);
void ClientRun(Clients& clientele, char* ip, char* username, int port, bool& brod);


int main()
{

	WSADATA wsadata;
	WSAStartup(WINSOCK_VERSION, &wsadata);

	Clients clientele{};
	Servers serv{};

	int choice = 0;
	char username[100];
	bool brod;
#pragma region UserInput
#if 0
	int charSize;
	char ip[100];
	int port = 0;


	cout << "Please input your server's IP address\n";
	cin >> ip;
	cout << "IP taken...\n\n";

	cout << "Please input your server's Port number\n";
	cin >> port;
	cout << "Port noted\n\n";
#endif
#pragma endregion

#pragma region AutoInput
#if 1

	char ip[] = { "127.0.0.1" };
	cout << "Your server's IP address is " << ip << '\n';

	int port = 31337;
	cout << "Your server's Port number is " << port << '\n';
#endif
#pragma endregion
	//use getline for whitespace otherwise see garbage 
	// cin.ignore and clear
	do
	{
		cout << "Would you like to Brodcast?\n1. yes\n2. no\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			brod = true;
			break;
		}
		case 2:
		{
			brod = false;
			break;
		}
		};

	} while (choice != 1 && choice != 2);

	do
	{
		cout << "Choose Server or Client\n";
		cout << "1. Server\n2. Client\n";
		cin >> choice;
	} while (choice != 1 && choice != 2);

	switch (choice)
	{
	case 1:
	{
		ServerRun(serv, port, brod); //continuous run = select, setinit, listen, accept
		break;

	}

	case 2:
	{


		ClientRun(clientele, ip, username, port, brod);
		break;
	}
	};

	return WSACleanup();
}

void ServerRun(Servers& serv, int port, bool& brod)
{
	if (brod)
	{
		serv.sBase.udpSocket = serv.UDPSocketInit(serv.sBase.udpSocket);

		//bind(serv.sBase.udpSocket, );
	}
	Clients client;

	serv.sBase.listener = serv.TCPSocketInit(serv.sBase.listener);
	serv.sBase.comSocket = serv.TCPSocketInit(serv.sBase.comSocket);
	serv.SocketBind(serv, port);
	serv.SocketListen(serv, 3);
	serv.isConnected = false;

	while (serv.isactive)
	{
		serv.isRead = false;
		if (!serv.isConnected)
		{
			char* message = new char[27];
			serv.AcceptConnect(serv);
			serv.Read(serv, message, client.cBase.bufsize);
		}
		else
		{
			char* chatMessage = new char[50];
			serv.Read(serv, chatMessage, client.cBase.bufsize);

		}

	}

	cout << "Server stopped\n";

}

void ClientRun(Clients& clientele, char* ip, char* username, int port, bool& brod)
{
	if (brod)
	{
		Servers serv;
		clientele.cBase.udpSocket = clientele.UDPSocketInit(clientele.cBase.udpSocket);
		int brodsize = 50;
		char brodMessage[50];
		cout << "send a message up to 50 characters\nBrodcast message: ";
		cin >> brodMessage;
		sendto(clientele.cBase.udpSocket, brodMessage, brodsize, 0, (SOCKADDR*)&serv.sBase.addrIn, brodsize);
		//recvfrom(clientele.cBase.udpSocket,);
	}

	Servers server;
	clientele.cBase.tcpSocket = clientele.TCPSocketInit(clientele.cBase.tcpSocket);
	clientele.isConnected = false;
	while (clientele.isactive)
	{
		bool sent = true;
		if (!clientele.isConnected)
		{
			clientele.SocketConnect(clientele, ip, port);
			if (clientele.isConnected)
			{
				clientele.UsernameIn(clientele.cBase, username);
				clientele.CommandIn(clientele.cBase, username);
			}
			if (!clientele.isactive)
			{
				break;
			}
			uint8_t size = 27;
			clientele.cBase.bufsize = size;
			char sendbuf[27];
			for (int i = 0; i < sizeof(clientele.cBase.command); i++)
			{
				sendbuf[i] = clientele.cBase.command[i];

			}
			clientele.Sender(clientele.cBase.tcpSocket, sendbuf, clientele.cBase.bufsize, sent);
		}
		else
		{
			int mSize = 50;
			char message[50];
			clientele.cBase.bufsize = mSize;
			cout << "Message: ";
			cin >> message;
			char* buffer = message;
			clientele.Sender(clientele.cBase.tcpSocket, buffer, clientele.cBase.bufsize, sent);
		}

	}
	cout << "Client has closed";
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
