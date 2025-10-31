#include "Client.h"

#include <fstream>
#include <string>
#include <MyLib/My_String.h>

const char* CLIENTS_FILE_NAME = "CLIENTS.txt";

using namespace Core;

bool Core::IsExistedClientByAccountNumber(const std::string& AccountNumber, const std::vector<stClient>& vClients)
{
	if (FindClientByAccountName(AccountNumber, LoadClientsFromFile()) != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Core::AddNewClient(std::vector<stClient>& vClients, const stClient& NewCLient)
{
	if (!IsExistedClientByAccountNumber(NewCLient.AccountNumber, vClients))
	{
		vClients.push_back(NewCLient);
		SaveClientToFile(NewCLient);

		return true;
	}
	else
	{
		return false;
	}
}

void Core::RefreshClientsVector(std::vector<stClient>& vClients)
{
	vClients = LoadClientsFromFile();
}

std::string Core::ConvertClientRecoredToLine(const stClient& Client, const char* separator)
{
	std::string Line = "";

	Line += Client.AccountNumber + separator;
	Line += Client.Name + separator;
	Line += Client.PinCode + separator;
	Line += Client.PhoneNumber + separator;
	Line += std::to_string(Client.Balance);

	return Line;
}

void Core::SaveClientsToFile(const std::vector<stClient>& vClients)
{
	std::fstream File;
	File.open(CLIENTS_FILE_NAME, std::ios::out); // write mode

	if (File.is_open())
	{
		for (const stClient& client : vClients)
		{
			if (!client.markForDelete)
			{
				File << ConvertClientRecoredToLine(client, "//#//");
				File << std::endl;
			}
		}
	}
	File.close();
}

void Core::SaveClientToFile(const stClient& Client)
{
	std::fstream File;
	File.open(CLIENTS_FILE_NAME, std::ios::out | std::ios::app); // appined mode

	if (File.is_open())
	{
		File << ConvertClientRecoredToLine(Client, "//#//");
		File << std::endl;
	}
	File.close();
}

stClient Core::ConvertClientLineToRecored(const std::string& line)
{
	stClient Client;

	std::vector<std::string> vClinetData = String::SliptString("//#//", line);

	Client.AccountNumber = vClinetData[0];
	Client.Name = vClinetData[1];
	Client.PinCode = vClinetData[2];
	Client.PhoneNumber = vClinetData[3];
	Client.Balance = std::stof(vClinetData[4]);

	return Client;
}

std::vector<stClient> Core::LoadClientsFromFile()
{
	std::vector<stClient> vClients;

	std::fstream File;
	File.open(CLIENTS_FILE_NAME, std::ios::in); // Read Mode

	if (File.is_open())
	{
		std::string line;
		while (std::getline(File, line))
		{
			stClient client = ConvertClientLineToRecored(line);
			vClients.push_back(client);
		}
	}
	File.close();

	return vClients;
}

short Core::FindClientByAccountName(const std::string& AccountName, const std::vector<stClient>& vClients)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == AccountName)
		{
			return i;
		}
	}
	return -1;
}

bool Core::DeleteClietByAccoutnNumber(const std::string& AccountNumber, std::vector<stClient>& vClients)
{
	short Index;
	if ((Index = FindClientByAccountName(AccountNumber, vClients)) != -1)
	{
		vClients[Index].markForDelete = true;
		SaveClientsToFile(vClients);

		RefreshClientsVector(vClients);
		return true;
	}
	else
	{
		return false;
	}
}

bool Core::UpdataClientByAccountName(const std::string& AccountNumber, const std::string& newName,
	const std::string& newPinCode, const std::string& newPhoneNumber, float newBalance, std::vector<stClient>& vClients)
{
	short Index;
	if (((Index = FindClientByAccountName(AccountNumber, vClients))) != -1)
	{
		vClients[Index].Name = newName;
		vClients[Index].PinCode = newPinCode;
		vClients[Index].PhoneNumber = newPhoneNumber;
		vClients[Index].Balance = newBalance;

		SaveClientsToFile(vClients);

		return true;
	}
	else
	{
		return false;
	}
}

bool Core::DepositByAccountNumber(float Ammount, const std::string& AccountNumber, std::vector<stClient>& vClients)
{
	short Index;
	if ((Index = FindClientByAccountName(AccountNumber, vClients)) != -1)
	{
		vClients[Index].Balance += Ammount;
		SaveClientsToFile(vClients);

		return true;
	}
	return false;
}

bool Core::WithdrawByAccountNumber(float Ammount, const std::string& AccountNumber, std::vector<stClient>& vClients)
{
	short Index;
	if ((Index = FindClientByAccountName(AccountNumber, vClients)) != -1)
	{
		if (vClients[Index].Balance >= Ammount)
		{
			vClients[Index].Balance -= Ammount;
			std::cout << vClients[Index].Balance;
			SaveClientsToFile(vClients);

			return true;
		}
	}
	return false;

}
