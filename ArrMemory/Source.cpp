#include <iostream>
#include "ConnectionController.h"


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ConnectionController cc("127.0.0.1", 1111);

	return 0;
}