#include <Windows.h>
#include <string>
#include <iostream>

#include "calculator/calculator.hpp"

static calculator::calculator_t my_calculator{};

int main()
{
	SetConsoleTitleA("Basic Calculator");
	std::printf("Welcome to the basic calculator project. Input an expression and it will output evaluation.\n");

	std::string input{};
	while (std::getline(std::cin, input))
	{
		double result = my_calculator.calculate(input);
		std::printf("Result: %.8f\n", result);
	}

	return 0;
}