#include "ConnectionController.h"

void ConnectionController::Connect()
{
	_socket = socket(AF_INET, SOCK_STREAM, NULL);
	//Делаем попытку присоединиться к серверу:
	if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		//std::cout << "Error: failed connect to server. \n";
		throw "Error: failed connect to server.";
	}
	std::cout << "Connected to server of hosital." << std::endl;
}

ConnectionController::ConnectionController(const char* ip_addr, int port)
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(ip_addr);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	Connect();
}

void ConnectionController::SendRequest(const RequestType req)
{
	send(_socket, (char*)&req, sizeof(RequestType), NULL);
}

void ConnectionController::SendString(const std::string& str)
{
	int str_size = str.size();
	send(_socket, (char*)&str_size, sizeof(int), NULL);
	send(_socket, str.c_str(), str_size, NULL);
}

std::string ConnectionController::ReceiveString()
{
	int msg_size;
	recv(_socket, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1];
	msg[msg_size] = '\0';
	recv(_socket, msg, msg_size, NULL);
	return msg;
}

SOCKET ConnectionController::GetSocket() const
{
	return _socket;
}
