#include "Client.h"

//Initializes sockets
SOCKET Clients::TCPSocketInit(SOCKET sock)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		cout << "Client Socket failed to be created\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Client Socket was created\n";
	}
	return sock;
}

SOCKET Clients::UDPSocketInit(SOCKET sock)
{
	sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		cout << "Server UDP Socket failed to be created\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Server UDP Socket was created\n";
	}
	return sock;
}

//Connects Sockets to Server
void Clients::SocketConnect(Clients& clientele, char* address, int port)
{
	bool loop = true;

	clientele.cBase.sockIn.sin_family = AF_INET;
	int check = inet_pton(clientele.cBase.sockIn.sin_family, address, &clientele.cBase.inAddr);
	if (check == SOCKET_ERROR || check == 0)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNRESET)
		{
			shutdown(clientele.cBase.tcpSocket, 2);
			closesocket(clientele.cBase.tcpSocket);
		}
		else
		{

		}
		cout << "inet_pton failed\n";
		cout << error << " erorr found\n";
	}

	clientele.cBase.sockIn.sin_port = htons(port);
	clientele.cBase.sockIn.sin_addr = clientele.cBase.inAddr;


	cout << "Connecting.";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(2000);
	printf("\33[2K\r");

	int result = connect(clientele.cBase.tcpSocket, (SOCKADDR*)&clientele.cBase.sockIn, sizeof(clientele.cBase.sockIn));

	if (result == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNRESET)
		{
			shutdown(clientele.cBase.tcpSocket, 2);
			closesocket(clientele.cBase.tcpSocket);
		}
		cout << "Faulty connection, socket did not connect\n";
		cout << error << " erorr found\n";
	}
	else
	{
		//clientele.cBase.ComSocket = clientele.cBase.tcpSocket;
		clientele.isConnected = true;
		cout << "Connected to Network\n";
	}
}

int userCount = 0;
//prompts user for a username that is 15 characters long
void Clients::UsernameIn(Client& clientele, char* username)
{
	bool isformat;
	do
	{
		cout << "Enter Your Username (up to 15 characters long)\n";
		cin >> username;
		if (sizeof(username) > 15)
		{
			cout << "too many characters";
		}
		else if (sizeof(username) <= 0)
		{
			cout << "too short";
		}
		else
		{
			clientele.userID[userCount] = username;
			userCount++;
			isformat = true;
		}
	} while (!isformat);
}

//prompts for a command to register or exit
void Clients::CommandIn(Client& clientele, char* username)
{
	char command[10];
	string comStr;
	bool isCom = true;
	do
	{
		cout << "Type $register, $getlist, or $exit.\n";
		cout << "$register - enables chat mode\n";
		cout << "$getlist - shows a list of the amount of currently registered users\n";
		cout << "$exit - disconnects user\n";
		cin >> command;

		if (command[0] == '$')
		{
			bool isCommand = false;

			int goodCounter = 0;
			int badCounter = 0;

			char regComm[10] = "$register";
			char listComm[9] = "$getlist";
			char exiComm[6] = "$exit";

			for (int i = 1; i < 9; i++)
			{
				if (command[i] == regComm[i])
				{
					goodCounter++;
					if (goodCounter == 8)
					{
						isCommand = true;
					}
				}
				else if (command[i] == exiComm[i])
				{
					if (goodCounter == 4)
					{
						isCommand = true;
					}
					else
					{
						goodCounter++;
					}
				}
			}

			if (!isCommand)
			{
				goodCounter = 0;
				for (int i = 1; i < 8; i++)
				{

					if (command[i] == listComm[i])
					{
						goodCounter++;
					}
				}
			}

			if (goodCounter == 8)
			{
				comStr.append(command);
				comStr.append("<");
				comStr.append(username);
				comStr.append(">");
				for (int i = 0; i < comStr.size(); i++)
				{
					clientele.command[i] = comStr.c_str()[i];
				}
				isCom = true;
			}
			else if (goodCounter == 7)
			{
				for (int i = 0; i < sizeof(command); i++)
				{
					clientele.command[i] = command[i];
				}
				isCom = true;
			}
			else if (goodCounter == 4)
			{
				cout << "Exiting program\n";

				shutdown(clientele.tcpSocket, 2);
				closesocket(clientele.tcpSocket);
				isactive = false;
				isCom = true;
			}
		}
		else
		{
			cout << "type one of the two commands above (include $)\n";
			isCom = false;
		}
	} while (!isCom);
}

//sends the entire message to the Server
int Clients::FullSend(SOCKET& comSocket, char* data, uint16_t length)
{
	int result;
	int bytesSent = 0;

	while (bytesSent < length)
	{
		result = send(comSocket, (char*)data + bytesSent, length - bytesSent, 0);

		if (result <= 0)
			return result;

		bytesSent += result;
	}

	return bytesSent;
}

//sends message to Server
void Clients::Sender(SOCKET& comSocket, char* data, uint16_t length, bool isSent)
{
	int result = FullSend(comSocket, (char*)&length, 1);
	if ((result == SOCKET_ERROR) || (result == 0))
	{
		int error = WSAGetLastError();
		if (error == WSAECONNRESET)
		{
			shutdown(comSocket, 2);
			closesocket(comSocket);
		}
		cout << "Message reached a dead end...\n";
		return;

	}
	else
	{
		result = FullSend(comSocket, data, length);
		if ((result == SOCKET_ERROR) || (result == 0))
		{
			int error = WSAGetLastError();
			if (error == WSAECONNRESET)
			{
				shutdown(comSocket, 2);
				closesocket(comSocket);
			}
			cout << "Message reached a dead end...\n";
			return;

		}
		else
		{
			if (isSent)
			{
				cout << "Message was sent\n";
				isSent = false;
			}
		}
	}
}
