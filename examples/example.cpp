#include <iostream>
#include <string>

#include "../FuzzBuzz.h" // include the FuzzBuzz library

int main() {
	FuzzBuzz fbuzz;	// declare a FuzzBuzz object
	std::string input;

	fbuzz.load("sample-input-file.txt");

	while(1) {
		std::cout << "Enter input string: ";
		getline(std::cin, input);
		std::cout << "Best match for \"" << input << "\" = " << "\"" << fbuzz.best(input) << "\"" << std::endl;
	}
}