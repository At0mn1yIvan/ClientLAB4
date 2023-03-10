#pragma comment(lib, "ws2_32.lib") // 
#include <winsock2.h> // Библиотека для работы с сетью (2 версия)
#include <iostream>
#include <string>

#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler() {
	int msg_size;
	while (true) {
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
	}
}

int main() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);

	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	//Делаем попытку присоединиться к серверу:
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server. \n";
		return 1;
	}
	std::cout << "Connected to server" << std::endl;
	//char msg[256];
	////Примем и запишем отправленные сервером данные в только что созданную переменную
	//recv(Connection, msg, sizeof(msg), NULL); // Connection - сокет, который хранит соединение с сервером, от которого придет сообщение. Второй параметр - переменная в которую будет записываться сообщение
	//std::cout << msg << std::endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	std::string msgl;
	while (true) {
		std::getline(std::cin, msgl);
		int msg_size = msgl.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msgl.c_str(), msg_size, NULL);
		Sleep(10); // пауза
	}

	system("pause");


	return 0;
}
