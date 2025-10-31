#pragma once
#include <iostream>

namespace Inputs
{
	float ReadPositiveNumber(const char* message);
	float ReadNumber(const char* message);
	float ReadNumber(const char* message, float from, float to);
	int GetRandomNumber(int min, int max);

	std::string ReadString(const char* message);

	char ReadChar(const char* message);
}