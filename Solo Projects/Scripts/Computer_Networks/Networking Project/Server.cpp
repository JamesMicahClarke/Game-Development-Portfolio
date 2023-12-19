#include "Server.h"

using namespace std;
void Servers::SetInit(Servers& serv)
{
	FD_ZERO(&serv.sBase.masterSet);
	FD_SET(serv.sBase.listener, &serv.sBase.masterSet);
	serv.sBase.readySet = serv.sBase.masterSet;
	cout << "Sets Initialized\n";
}

SOCKET Servers::TCPSocketInit(SOCKET sock)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		/*if (error == WSAECONNRESET)
		{
			shutdown(sock, 2);
			closesocket(sock);
		}*/
		cout << "Server TCP Socket failed to be created\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Server TCP Socket was created\n";
	}
	return sock;
}

SOCKET Servers::UDPSocketInit(SOCKET sock)
{
	sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		/*if (error == WSAECONNRESET)
		{
			shutdown(sock, 2);
			closesocket(sock);
		}*/
		cout << "Server UDP Socket failed to be created\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Server UDP Socket was created\n";
	}
	return sock;
}

//Binds sockets
void Servers::SocketBind(Servers& serv, int port)
{
	serv.sBase.addrIn.sin_family = AF_INET;
	serv.sBase.addrIn.sin_addr.S_un.S_addr = INADDR_ANY;
	serv.sBase.addrIn.sin_port = htons(port);

	int result = bind(serv.sBase.listener, (SOCKADDR*)&serv.sBase.addrIn, sizeof(serv.sBase.addrIn));
	if (result == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNRESET)
		{
			shutdown(serv.sBase.listener, 2);
			closesocket(serv.sBase.listener);
		}
		cout << "Bind Failed\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Bind was Successful\n";

	}
}

//Sets sockets to listen mode
void Servers::SocketListen(Servers& serv, int connections)
{
	int result = listen(serv.sBase.listener, connections);
	if (result == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNRESET)
		{
			shutdown(serv.sBase.listener, 2);
			closesocket(serv.sBase.listener);
		}
		cout << "Server is deaf\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Server can hear you loud and clear!\n";
	}
	serv.SetInit(serv);
}


//selects ready sockets
void Servers::Selection(Servers& serv)
{
	serv.sBase.timeout.tv_sec = NULL;
	int selection = select(0, &serv.sBase.readySet, NULL, NULL, &serv.sBase.timeout);
	if (selection == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		if (error == WSAECONNRESET)
		{
			shutdown(serv.sBase.listener, 2);
			closesocket(serv.sBase.listener);

			/*shutdown(serv.sBase.comSocket, 2);
			closesocket(serv.sBase.comSocket);*/
		}
		cout << "Selection failed\n";
		cout << error << " erorr found\n";
	}
	else
	{
		cout << "Socket Selected\n";
	}

}

//Accepts connections
void Servers::AcceptConnect(Servers& serv)
{
	Selection(serv);

	int setCheck;
	if (FD_ISSET(serv.sBase.listener, &serv.sBase.readySet))
	{
		for (int i = 0; i < serv.sBase.readySet.fd_count; i++)
		{
			serv.sBase.comSocket = accept(serv.sBase.listener, NULL, NULL);
			if (serv.sBase.comSocket == INVALID_SOCKET)
			{
				int error = WSAGetLastError();
				if (error == WSAECONNRESET)
				{
					shutdown(serv.sBase.listener, 2);
					closesocket(serv.sBase.listener);

					/*shutdown(serv.sBase.comSocket, 2);
					closesocket(serv.sBase.comSocket);*/
				}
				cout << "Connection Denied\n";
				cout << error << " erorr found\n";

			}
			else
			{
				SOCKET temp = serv.sBase.comSocket;
				int count = serv.sBase.masterSet.fd_count;
				for (int i = 0; i < serv.sBase.masterSet.fd_count + 1; i++)
				{
					if (serv.sBase.masterSet.fd_array[i] == 0)
					{
						if (i == serv.sBase.masterSet.fd_count + 1)
						{
							break;
						}
						serv.sBase.masterSet.fd_array[i] = temp;
						count++;
					}

				}
				serv.sBase.masterSet.fd_count = count;
				isConnected = true;
				cout << "Connection accepted\n";
			}
		}
	}
	else
	{
		cout << "FD_Set was not set\n";
	}
}

//recvs the entire message sent by client
int Servers::FullRecieve(SOCKET& s, char* buf, int len)
{
	int total = 0;

	do
	{
		int ret = recv(s, buf + total, len - total, 0);
		if (ret < 1)
			return ret;
		else
			total += ret;

	} while (total < len);

	return total;
}

void Servers::Read(Servers& serv, char* message, int size)
{
	int total = 0;
	int stopCount = 0;
	int result = 0;

	result = FullRecieve(serv.sBase.comSocket, (char*)&size, 1);
	if ((result == SOCKET_ERROR))
	{
		if (stopCount == 0 || !isConnected)
		{
			int error = WSAGetLastError();
			if (error == WSAECONNRESET)
			{
				shutdown(serv.sBase.listener, 2);
				closesocket(serv.sBase.listener);

				shutdown(serv.sBase.comSocket, 2);
				closesocket(serv.sBase.comSocket);
			}
			else {
				return;
			}
			cout << error << " erorr found\n";
			stopCount++;
			return;
		}
		else if ((stopCount > 0) && isConnected)
		{
			stopCount = 0;
		}
	}
	else if (result == 0)
	{
		if (stopCount == 1)
		{

			cout << "Graceful disconnection has occured";
			stopCount = 0;;
		}
			return;
	}
	else
	{
		cout << "recieving message.";
		Sleep(1000);
		cout << ".";
		Sleep(1000);
		cout << ".\n";
		Sleep(2000);

		message = new char[size];
		result = FullRecieve(serv.sBase.comSocket, message, size);
		if ((result == SOCKET_ERROR) || (result == 0))
		{
			int error = WSAGetLastError();
			if (error == WSAECONNRESET)
			{
				shutdown(serv.sBase.listener, 2);
				closesocket(serv.sBase.listener);

				shutdown(serv.sBase.comSocket, 2);
				closesocket(serv.sBase.comSocket);
			}
			else {
				return;
			}
			cout << error << " erorr found\n";
			return;

		}
		else if (result == 0)
		{
			if (stopCount == 0)
			{
				cout << "Graceful disconnection has occured";
				stopCount++;
			}
			return;
		}
		else
		{
			char commCheck1[10] = { "$register" };
			char commCheck2[9] = { "$getlist" };
			char commCheck3[6] = { "$exit" };
			int goodcount = 0;
			if (message[0] == commCheck1[0])
			{
				for (int i = 1; i < 9; i++)
				{
					if (message[i] == commCheck1[i])
					{
						goodcount++;
					}
					else if (message[i] == commCheck3[i])
					{
						goodcount++;
					}
				}

				goodcount = 0;
				for (int i = 1; i < 8; i++)
				{
					if (message[i] == commCheck2[i])
					{
						goodcount++;
					}
				}
			}

			if (goodcount == 8)
			{
				system("cls");
				serv.sBase.registered++;
				cout << "Registered: " << serv.sBase.registered << "/4\n";

				if (serv.sBase.registered > 4)
				{
					cout << "Server is full.";
					for (int i = 4; i < serv.sBase.readySet.fd_count; i++)
					{
						shutdown(serv.sBase.readySet.fd_array[i], 2);
						closesocket(serv.sBase.readySet.fd_array[i]);
					}
				}
				else
				{
					int userI = 0;
					for (int i = 10; i < 25; i++)
					{
						if (message[i] != '>')
						{
							serv.sBase.userID[userI] = message[i];
							userI++;

						}
						else
						{
							if (serv.sBase.userlist[serv.sBase.listCount] == NULL)
							{
								serv.sBase.userlist[serv.sBase.listCount] = serv.sBase.userID;
							}
							serv.sBase.listCount++;

							cout << serv.sBase.userID << " has joined.\n";
							break;
						}

					}
				}
			}
			else if (goodcount == 7)
			{
				if (serv.sBase.listCount != 0)
				{

					cout << "There are currently " << serv.sBase.listCount << " users in the chatroom\n";


					cout << "Users: ";
					for (int i = 0; i < serv.sBase.listCount; i++)
					{
						cout << serv.sBase.userlist[i] << ",";
					}
					cout << "\n";
				}
				else
				{

					cout << "User List is currently empty\n";
				}
			}
			else if (goodcount == 4)
			{
				for (int i = 0; i < sizeof(serv.sBase.userlist[serv.sBase.listCount]); i++)
				{
					serv.sBase.userlist[serv.sBase.listCount][i] = '\0';

				}
				serv.sBase.listCount--;

				shutdown(serv.sBase.comSocket, 2);
				closesocket(serv.sBase.comSocket);

			}

			cout << "Message sent: " << message << "\n";
		}
	}
}
