#include "My_Inputs.h"

#include<string>


using namespace Inputs;

float Inputs::ReadPositiveNumber(const char* message)
{
	float number;

	do
	{
		std::cout << message;
		std::cin >> number;
	} while (number < 0);

	return number;
}

float Inputs::ReadNumber(const char* message)
{
	float number;

	std::cout << message;
	std::cin >> number;

	return number;
}

float Inputs::ReadNumber(const char* message, float from, float to)
{
	float number;

	do
	{
		std::cout << message;
		std::cin >> number;
	} while (number < from || number > to);

	return number;
}

int Inputs::GetRandomNumber(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

std::string Inputs::ReadString(const char* message)
{
	std::string S1;
	std::cout << message;
	std::getline(std::cin >> std::ws, S1);
	return S1;
}

char Inputs::ReadChar(const char* message)
{
	char C;

	std::cout << message;
	std::cin >> C;

	return C;
}

