#pragma once

#include "ConnectionController.h"


class DoctorApplication
{
private:
	ConnectionController _conContr;
	void Login();
public:
	Patient GetPatient();
};

