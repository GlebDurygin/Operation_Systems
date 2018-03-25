#include "stdafx.h"
#include "util.h"
int util::readInt() {
	int result = 0;
	std::string input;
	bool valid = false;

	while (!valid) {
		std::cin >> input;
		try {
			result = std::stoi(input);
			valid = true;
		}
		catch (...) {
			valid = false;
			std::cout << "Invalid number." << std::endl;
		}
	}

	return result;
}