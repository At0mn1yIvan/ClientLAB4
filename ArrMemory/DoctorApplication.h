 #pragma once

#include "ConnectionController.h"


class DoctorApplication
{
private:
	static DataHandler _optData;
	ConnectionController _conContr;
	void Login();
public:
	Patient GetPatient(const std::string& pat) {

		return _optData.Unpacking(pat);
	
	
	}
};

