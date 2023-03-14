#pragma once
#pragma comment(lib, "ws2_32.lib") // 
#include <winsock2.h> // ���������� ��� ������ � ����� (2 ������)
#include <string>
#include <iostream>
#include "Patient.h"

#pragma warning(disable: 4996)

//Client
class ConnectionController
{
private:
	SOCKET _socket;
	std::string _addressIp;
	SOCKADDR_IN addr;
	void Connect() {
		_socket = socket(AF_INET, SOCK_STREAM, NULL);
		//������ ������� �������������� � �������:
		if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
			//std::cout << "Error: failed connect to server. \n";
			throw "Error: failed connect to server.";
		}
		std::cout << "Connected to server" << std::endl;
		////������ � ������� ������������ �������� ������ � ������ ��� ��������� ����������
		//recv(Connection, msg, sizeof(msg), NULL); // Connection - �����, ������� ������ ���������� � ��������, �� �������� ������ ���������. ������ �������� - ���������� � ������� ����� ������������ ���������
		//std::cout << msg << std::endl;

		ClientSender();

	}
	std::string GetData();
	
public:
	ConnectionController() {
		WSAData wsaData;
		WORD DLLVersion = MAKEWORD(2, 2);
		if (WSAStartup(DLLVersion, &wsaData) != 0) {
			std::cout << "Error" << std::endl;
			exit(1);
		}

		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;

		Connect();

		
	}





	void ClientSender() {
		std::string msgl;
		while (true) {
			std::getline(std::cin, msgl);
			int msg_size = msgl.size();
			send(_socket, (char*)&msg_size, sizeof(int), NULL);
			send(_socket, msgl.c_str(), msg_size, NULL);
			Sleep(1); // �����

			recv(_socket, (char*)&msg_size, sizeof(int), NULL);
			char* msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(_socket, msg, msg_size, NULL);
			std::cout << msg << std::endl;
			delete[] msg;

		}
	}
};
