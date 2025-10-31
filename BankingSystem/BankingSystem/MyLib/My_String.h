#pragma once

#include <iostream>
#include <vector>

namespace String
{
	enum enCharType { Capital, Small, Space, Symbol };

	std::string UpperAllString(std::string str);
	std::string LowerAllString(std::string str);
	std::string InvertAllString(std::string& str);
	std::vector<std::string> SliptString(const std::string& delimeter, std::string stringScourse);
	std::string JoinString(const std::string& delimeter, const std::vector<std::string>& vStrings);
	std::string JoinString(const std::string& delimeter, std::string strings[], int size);
	std::string TrimStringLeft(const std::string& str);
	std::string TrimStringRight(const std::string& str);
	std::string TrimString(const std::string& str);
	std::string ReplaceWordInString(std::string string, const std::string& oldWord, const std::string& newWord, bool machCase = true);
	unsigned short CountLatterInString(const std::string& str, enCharType charType);
	unsigned short CountLatterInString(std::string& str, char LatterToSearch, bool isCaseSinsetive = true);
	int CountWordsInString(const std::string& stringScourse);
	void PrintStringDetails(const std::string& str);

	enCharType GetCharType(char Char);
	char InvertCharacter(char Char);
	void PrintCharType(char Char);
	bool IsVowel(char Char);
}