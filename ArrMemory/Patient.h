#pragma once
#include <string>

enum class State {
	Regular,
	Medium,
	Critical,
};


class Patient
{
private:
	std::string _name;
	std::string _surname;
	std::string _patronymic;
	State _patientState;
public:
	Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state) : _name(firstName),
					   _surname(lastName),
					   _patronymic(patronymic),
					   _patientState(state)
	{}

	std::string GetFirstName() const {
		return _name;
	}
	std::string GetLastName() const {
		return _surname;
	}
	std::string GetPatronymic() const {
		return _patronymic;
	}
	State GetState() const {
		return _patientState;
	}


};


class VIP_Patient : public Patient {
private:
	size_t moneyAmount;
public:
	VIP_Patient(const std::string& firstName,
		const std::string& lastName,
		const std::string& patronymic,
		State state,
		size_t _moneyAmount = 1000) : Patient(firstName, lastName, patronymic, state), moneyAmount(_moneyAmount) {

	}

	size_t getMoney() const { return moneyAmount; }
};




