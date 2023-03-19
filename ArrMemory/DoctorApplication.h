#pragma once

#include "ConnectionController.h"

class DoctorApplication
{
private:
	static DataHandler _optData;
	static ConnectionController _conContr;
	bool _logged;

	void Login();
	void Logout();
	void GetPatient();

public:
	DoctorApplication();
	void StartWork();
};

