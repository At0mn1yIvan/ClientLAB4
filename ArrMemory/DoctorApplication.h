#pragma once


#include "ConnectionController.h"

class DoctorApplication
{
private:
	static DataHandler _optData;
	static ConnectionController _conContr;
	bool _logged;

	void Login() {
		LoggingResponse lr;
		do {
			_conContr.SendRequest(RequestType::LOGIN);

			std::string login;
			std::cout << "Enter your Login:\n";
			std::getline(std::cin, login);

			std::string password;
			std::cout << "Enter your password:\n";
			std::getline(std::cin, password);
			
			_conContr.SendString(login);
			_conContr.SendString(password);


			recv(_conContr.GetSocket(), (char*)&lr, sizeof(LoggingResponse), NULL);
			if (lr == LoggingResponse::AOS)
				std::cout << "Already connected to server." << std::endl;
			else if (lr == LoggingResponse::INCORRECT)
				std::cout << "Invalid login or password." << std::endl;
		} while (lr != LoggingResponse::CORRECT);
		std::cout << "Successfully connected to server." << std::endl;
		_logged = true;
	}

	void Logout() {
		_conContr.SendRequest(RequestType::LOGOUT);
		_logged = false;
		std::cout << "Log out successfully." << std::endl;

	}

	void GetPatient() {
		_conContr.SendRequest(RequestType::GETPATIENT);
		;
		int msg_size;
		std::string patient_str = _conContr.ReceiveStr();
		try {
			Patient patient = _optData.Unpacking(patient_str);
			std::cout << "Card of patient:" << std::endl;
			std::cout << "First Name: " << patient.GetFirstName() << std::endl;
			std::cout << "Last Name: " << patient.GetLastName() << std::endl;
			std::cout << "Patronymic: " << patient.GetPatronymic() << std::endl;
			std::cout << "State: " << (patient.GetState() == State::Regular ? "Regular" : (patient.GetState() == State::Medium ? "Medium" : "Critical")) << std::endl;
		}
		catch (nlohmann::json_abi_v3_11_2::detail::parse_error)
		{
			std::cout << patient_str << std::endl;
		}

	}

public:
	DoctorApplication() : _logged(false) {
		StartWork();
	}


	void StartWork() {
		while (true)
		{
			if (_logged) {
				int option;
				std::cout << "\nChoose an option:\n1 - Get Patient from queue.\n2 - Logout." << std::endl;
				std::cin >> option;
				switch (option)
				{
				case 1: {
					GetPatient();
					break;
				}
				case 2: {
					Logout();
					break;
				}
				}
			}
			else
			{
				std::cout << "You need to log in." << std::endl;
				Login();
			}
		}

	}

};

