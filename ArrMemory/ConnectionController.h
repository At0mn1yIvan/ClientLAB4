#pragma once
#pragma comment(lib, "ws2_32.lib") // 
#include <winsock2.h> // Библиотека для работы с сетью (2 версия)
#include <string>
#include <iostream>
#include "Patient.h"
#include "DataHandler.h"

#pragma warning(disable: 4996)

	enum class RequestType {
		LOGIN,
		GETPATIENT,
		LOGOUT,
	};

	enum class LoggingResponse {
		AOS,
		CORRECT,
		INCORRECT,
	};

//Client
	class ConnectionController
	{
	private:
		SOCKET _socket;
		//std::string _addressIp;
		SOCKADDR_IN addr;
		static DataHandler _optData;
		void Connect() {
			_socket = socket(AF_INET, SOCK_STREAM, NULL);
			//Делаем попытку присоединиться к серверу:
			if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
				//std::cout << "Error: failed connect to server. \n";
				throw "Error: failed connect to server.";
			}
			std::cout << "Connected to server" << std::endl;

			////Примем и запишем отправленные сервером данные в только что созданную переменную
			//recv(Connection, msg, sizeof(msg), NULL); // Connection - сокет, который хранит соединение с сервером, от которого придет сообщение. Второй параметр - переменная в которую будет записываться сообщение
		}




		//		recv(_socket, (char*)&msg_size, sizeof(int), NULL);
		//		msg = new char[msg_size + 1];
		//		msg[msg_size] = '\0';
		//		recv(_socket, msg, msg_size, NULL);
		//		//Patient pat = _optData.Unpacking(msg);
		//		std::cout << msg << std::endl;
		//		delete[] msg; // ???


	public:
		ConnectionController(const char* ip_addr, int port)
		{
			WSAData wsaData;
			WORD DLLVersion = MAKEWORD(2, 2);
			if (WSAStartup(DLLVersion, &wsaData) != 0) {
				std::cout << "Error" << std::endl;
				exit(1);
			}

			int sizeofaddr = sizeof(addr);
			//addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			addr.sin_addr.s_addr = inet_addr(ip_addr);
			//addr.sin_port = htons(1111);
			addr.sin_port = htons(port);
			addr.sin_family = AF_INET;

			Connect();


		}

		void SendRequest(const RequestType req)
		{
			send(_socket, (char*)&req, sizeof(RequestType), NULL);
		}


		void SendString(const std::string& str)
		{
			int str_size = str.size();
			send(_socket, (char*)&str_size, sizeof(int), NULL);
			send(_socket, str.c_str(), str_size, NULL);
		}

		std::string ReceiveStr()
		{
			int msg_size;
			recv(_socket, (char*)&msg_size, sizeof(int), NULL);
			char* msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(_socket, msg, msg_size, NULL);
			return msg;
		}

		LoggingResponse ReceiveLogResponse()
		{
			LoggingResponse resp;
			recv(_socket, (char*)&resp, sizeof(LoggingResponse), NULL);
			return resp;
		}

	SOCKET GetSocket() const
	{
		return _socket;
	}
};

