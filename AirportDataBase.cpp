#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main(void) {

	const short BUFF_SIZE = 1024;

	//Инициализация соккетных интерфейсов
	WSADATA wsData;

	int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		return 1;
	}
	else
		cout << "WinSock initialization is OK" << endl;

	//Создание сокета и его инициализация
	SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ServSock == INVALID_SOCKET) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(ServSock);
		WSACleanup();
		return 1;
	}
	else
		cout << "Server socket initialization is OK" << endl;

	//Привязка сокета к паре IP/порт
	in_addr ip_to_num;
	erStat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);
	if (erStat <= 0) {
		cout << "Error in IP translation to special numeric format" << endl;
		return 1;
	}

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(8080);

	erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));
	if (erStat != 0) {
		cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << endl;
		closesocket(ServSock);
		WSACleanup();
		return 1;
	}
	else
		cout << "Binding socket to Server info is OK" << endl;

	//Прослушивание привязанного порта для идентификации подключений
	erStat = listen(ServSock, SOMAXCONN);

	if (erStat != 0) {
		cout << "Can't start to listen to. Error # " << WSAGetLastError() << endl;
		closesocket(ServSock);
		WSACleanup();
		return 1;
	}
	else {
		cout << "Listening..." << endl;
	}

	//Подтверждение подключения
	sockaddr_in clientInfo;

	ZeroMemory(&clientInfo, sizeof(clientInfo));

	int clientInfo_size = sizeof(clientInfo);

	SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);

	if (ClientConn == INVALID_SOCKET) {
		cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << endl;
		closesocket(ServSock);
		closesocket(ClientConn);
		WSACleanup();
		return 1;
	}
	else
		cout << "Connection to a client established successfully" << endl;

	//Передача данных

	vector <char> servBuff(BUFF_SIZE);
	short packet_size = 0;

	while (true) {
		packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
		cout << "Client's message: " << servBuff.data() << endl;


		// Check whether server would like to stop chatting 
		if (servBuff[0] == 'x' && servBuff[1] == 'x') {
			shutdown(ClientConn, SD_BOTH);
			closesocket(ServSock);
			closesocket(ClientConn);
			WSACleanup();
			return 0;
		}

		//packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);

		if (packet_size == SOCKET_ERROR) {
			cout << "Can't send message to Client. Error # " << WSAGetLastError() << endl;
			closesocket(ServSock);
			closesocket(ClientConn);
			WSACleanup();
			return 1;
		}


	
	}



	return 0;
}