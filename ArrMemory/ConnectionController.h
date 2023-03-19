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
		void Connect();
		

	public:
		ConnectionController(const char* ip_addr, int port);
		void SendRequest(const RequestType req);
		void SendString(const std::string& str);
		std::string ReceiveString();
		//LoggingResponse ReceiveLogResponse();
		SOCKET GetSocket() const;
};

