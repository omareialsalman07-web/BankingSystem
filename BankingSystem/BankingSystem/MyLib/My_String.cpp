#include "My_String.h"

#include <cstdlib>
#include<string>
#include <ctime>

using namespace String;

std::string String::UpperAllString(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
			str[i] = std::toupper(str[i]);
	}

	return str;
}

std::string String::LowerAllString(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
			str[i] = std::tolower(str[i]);
	}

	return str;
}

std::string String::InvertAllString(std::string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ') // this is a latter or character
			str[i] = InvertCharacter(str[i]);
	}

	return str;

	return std::string();
}

void String::PrintStringDetails(const std::string& str)
{
	std::cout << "String length is        : " << str.length() << "\n";
	std::cout << "Capital latter count is : " << CountLatterInString(str, enCharType::Capital) << "\n";
	std::cout << "Small latter count is   : " << CountLatterInString(str, enCharType::Small) << "\n";
	std::cout << "Symbols count is        : " << CountLatterInString(str, enCharType::Symbol) << "\n";
	std::cout << "Spaces count is         : " << CountLatterInString(str, enCharType::Space) << "\n";
}

unsigned short String::CountLatterInString(const std::string& str, enCharType charType)
{
	unsigned short counter = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if (GetCharType(str[i]) == charType)
			counter++;
	}
	return counter;
}

unsigned short String::CountLatterInString(std::string& str, char LatterToSearch, bool isCaseSinsetive)
{
	if (!isCaseSinsetive)
	{
		LowerAllString(str);
		LatterToSearch = std::tolower(LatterToSearch);
	}

	unsigned short counter = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == LatterToSearch)
			counter++;
	}
	return counter;

}

std::vector<std::string> String::SliptString(const std::string& delimeter, std::string stringSourse)
{
	std::vector<std::string> vStringsRes;

	short pos = 0;
	std::string newWord;

	while ((pos = stringSourse.find(delimeter)) != std::string::npos)
	{
		newWord = stringSourse.substr(0, pos);
		if (!newWord.empty())
			vStringsRes.push_back(newWord);

		stringSourse.erase(0, pos + delimeter.length());
	}

	// Don't forget the last part (after last delimiter)
	if (!stringSourse.empty())
		vStringsRes.push_back(stringSourse);

	return vStringsRes;
}

std::string String::JoinString(const std::string& delimeter, const std::vector<std::string>& vStrings)
{
	std::string S = "";

	for (const std::string& word : vStrings)
	{
		S += word + delimeter;
	}

	return S.substr(0, S.length() - delimeter.length());
}

std::string String::JoinString(const std::string& delimeter, std::string strings[], int size)
{
	std::string S = "";

	for (int i = 0; i = size; i++)
	{
		S += strings[i] + delimeter;
	}

	return S.substr(0, S.length() - delimeter.length());
}

std::string String::TrimStringLeft(const std::string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			return str.substr(i, str.length() - 1);
		}
	}
}

std::string String::TrimStringRight(const std::string& str)
{
	for (int i = str.length(); i > 0; i--)
	{
		if (str[i] != ' ')
		{
			return str.substr(0, i + 1);
		}
	}
}

std::string String::TrimString(const std::string& str)
{
	return TrimStringLeft(TrimStringRight(str));;
}

std::string String::ReplaceWordInString(std::string string, const std::string& oldWord, const std::string& newWord, bool machCase)
{
	std::vector<std::string> vWords = SliptString(" ", string);

	for (std::string& word : vWords)
	{
		if (machCase)
		{
			if (word == oldWord)
				word = newWord; // update the maching vector element
		}
		else
		{
			if (LowerAllString(word) == LowerAllString(oldWord))
				word = newWord;
		}
	}
	return JoinString(" ", vWords);
}

int String::CountWordsInString(const std::string& stringScourse)
{
	return SliptString(" ", stringScourse).size();
}


enCharType String::GetCharType(char Char)
{
	enCharType CharType;

	if (Char == ' ') return enCharType::Space;

	int aciiForChar = int(Char);

	if (aciiForChar >= 64 && aciiForChar <= 90) // (A : 64 | Z : 90)
		return enCharType::Capital;
	else if (aciiForChar >= 97 && aciiForChar <= 122) // (a : 97 | z : 122)
		return enCharType::Small;
	else
		return enCharType::Symbol;

	return CharType;
}

char String::InvertCharacter(char Char)
{
	return  (GetCharType(Char) == enCharType::Capital) ? std::tolower(Char) : std::toupper(Char);
}

void String::PrintCharType(char Char)
{
	enCharType CharType = GetCharType(Char);
	switch (CharType)
	{
	case Capital:
		std::cout << "Capital Latter\n";
		break;
	case Small:
		std::cout << "Small Latter\n";
		break;
	case Symbol:
		std::cout << "Symbol\n";
		break;
	default:
		break;
	}
}

bool String::IsVowel(char Char)
{
	Char = tolower(Char);

	return ((Char == 'a') || (Char == 'e') || (Char == 'i') || (Char == 'o') || (Char == 'u'));
}