#pragma once
#include <iostream>
#include <vector>

namespace Core
{
	struct stClient
	{
		std::string AccountNumber;
		std::string Name;
		std::string PinCode;
		std::string PhoneNumber;
		float Balance = 0;

		bool markForDelete = false;
	};

	bool IsExistedClientByAccountNumber(const std::string& AccountNumber, const std::vector<stClient>& vClients);

	bool AddNewClient(std::vector<stClient>& vClients, const stClient& NewCLient);

	void RefreshClientsVector(std::vector<stClient>& vClients);

	// Related to save Clients ============
	std::string ConvertClientRecoredToLine(const stClient& Client, const char* separator);

	void SaveClientsToFile(const std::vector<stClient>& vClients);
	void SaveClientToFile(const stClient& Client);
	// =====================================

	// Related to loading Clients ==========
	stClient ConvertClientLineToRecored(const std::string& line);
	std::vector<stClient> LoadClientsFromFile();
	// ======================================

	short FindClientByAccountName(const std::string& AccountName, const std::vector<stClient>& vClients);

	bool DeleteClietByAccoutnNumber(const std::string& AccountNumber, std::vector<stClient>& vClients);

	bool UpdataClientByAccountName(const std::string& AccountNumber, const std::string& newName, 
		const std::string& newPinCode, const std::string& newPhoneNumber, float newBalance, std::vector<stClient>& vClients);

	// Related to Transactions
	bool DepositByAccountNumber(float Ammount, const std::string& AccountNumber, std::vector<stClient>& vClients);
	bool WithdrawByAccountNumber(float Ammount, const std::string& AccountNumber, std::vector<stClient>& vClients);
}